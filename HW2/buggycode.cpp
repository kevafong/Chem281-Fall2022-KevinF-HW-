
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>

struct header
{
  header* next;
  header* previous;
  uint64_t size;
};

class allocator
{
public:
  allocator();
  ~allocator();
  void* allocate(uint64_t size);
  void release(void*);
private:
  header head;
};

allocator::allocator() : head({NULL, NULL, 0}) // initializes head with no next, no previous, size 0
{
}

allocator::~allocator() //desctuctor
{
  header* buffer = head.next; // sets a buffer to next
  while (buffer)
    {
    header* nextbuffer = buffer->next;  // until buffer is null, sets nextbuffer to next
    release((char*) buffer + sizeof(header));     //releases buffer and header??
    buffer = nextbuffer;                // set buffer to nextbuffer
    }
}

void
allocator::release(void* mem) //releases memory
{
  header* buffer = (header*)((char*) mem - sizeof(header)); //remove header from mem
  uint64_t memsize = buffer->size;                          //set buffer size
  buffer->previous->next = buffer->next;                    // sets the next of the previous pointer to the next
  if (buffer->next) {
    buffer->next->previous = buffer->previous;              //*if theres a next, set the previous of next to previous, added brackets
    }    
  munmap(buffer, memsize); // unmaps buffer of memsize
}

void*
allocator::allocate(uint64_t size)
{
  const uint64_t offbits = 4095UL;
  const size_t allocSize = (size*sizeof(char*)+sizeof(header)+offbits) & (~offbits); // * allocSize should be size*size of the character
  header* buffer = (header*) mmap(NULL, allocSize, PROT_READ|PROT_WRITE,  // PROT_READ: pages may be read, PROT_WRITE: pages bay be accessed
				  MAP_PRIVATE|MAP_ANONYMOUS , -1 , 0);          // MAP_PRIVATE: create a private copy on write mapping, MAP_ANON: mapping is not backed by file, contents are zero, fd -1, offset 0
  buffer->next = head.next; //set next of buffers next to head next
  buffer->previous = &head; //set buffer previous as head
  buffer->size = allocSize; //header size
  head.next = buffer;       // set head next as the buffer
  return (char*) buffer+sizeof(header); // why am i returning the pointer 8 bytes away
}

double mean(const double* array, const uint64_t len)
{
  double mean = 0.d+00;
  for (uint64_t i=0; i<len; i++)
    mean += array[i];
  return mean/len; // *mean is sum of number of elements, need to divide by len of array
}

allocator* globalAllocator=NULL; // a null global allocator, will be replaced by allocator class if global is null 

void compute(double* a, double*& b, uint64_t len2) //calls allocator, global allocator
{
  uint64_t looplen = len2;
  static allocator getmem;
  globalAllocator = globalAllocator == NULL ? &getmem : globalAllocator; //ternary operator, if globalAllocator is NULL, it assign global to getme otherwise it returns the globalAllocator.
  if (b==NULL)  {
    b = (double*) globalAllocator->allocate(looplen); // currently returning another NULL pointer, should allocate a pointer for b
  }  
  for (unsigned int j=0; j<looplen; j++)
    b[j] = rand()%2 ? -a[j] : a[j];
}                                                     // destructor of allocator is called, this releases the data in b

uint64_t getarrdim()    //what does this do??
{
  uint64_t dim1 = rand();
  uint64_t dim2 = rand();
  uint64_t dim3 = rand();
  dim2 *=52;
  return dim2/dim3;
}

void getdata(const char* datafile, double*& buffer, uint64_t& len) // reading the address of len
{
  int fd = open(datafile, O_RDONLY);
  if (fd == -1)
    {
    printf("ERROR: File cannot open file %s\n", datafile);
    exit(1);  
    }
  read(fd, &len, sizeof(uint64_t)); // this reads 8 bytes into the address of len, first line of the data file is the size
  double* buffer2=new double[len];  // *allocate correct memory to a new buffer, assign pointer, delete the first.
  delete [] buffer;
  buffer=buffer2;
  read(fd, buffer, len*sizeof(double)); 
  close(fd);
}


int main(int argc, char* argv[])
{
  srand(222209);  //random seed
  if (argc < 2)   //check for data file
    {
    printf("Error, data file missing\n");
    exit(1);
    }
  const char* datafile = argv[1];   // store datafile as variable
  uint64_t dlen = 0;
  uint64_t dimarr = getarrdim();    // seems to generate a random int, 492
  double* arr = new double[dimarr]; // *change arr from array to pointer to allow change of pointer reference
  double* ptr1 = NULL;              // null pointer?
  getdata(datafile, arr, dlen);     // seems to store data from datafile to arr
  compute(arr, ptr1, dlen);         // computes a function of ptr on arr
  double meanvalue = mean(ptr1, dlen);  //what even
  printf("meanvalue %15le\n", meanvalue);   // print meanvalue
  printf("data sample\n");                  // this is just text
  for (unsigned int i=0; i<10; i++)
    printf("%le ", ptr1[i]);              // huh????
  printf("\n");
  return 0;
}
