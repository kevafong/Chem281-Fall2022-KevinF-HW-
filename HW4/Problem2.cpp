#include <iostream>
#include <stdlib.h>
#include <tuple>

std::tuple<int,int> RNGtuple(int maxsize)  {

    return std::tuple<int, int>{rand() % maxsize, rand() % maxsize};
}

template <typename T>
struct QueueNode    {
    T ID;
    QueueNode* next;
    QueueNode () : next(NULL)  {};
    QueueNode (T i) : next(NULL), ID(i)  {};
};

template <typename TypeNode>
class Queue {
    public:
    Queue() {
        TypeNode* dummy = new TypeNode(0);
        head = tail = dummy;
    }
    void insert(TypeNode& node)    {
        TypeNode* nn = new TypeNode(node);
        nn-> next = head->next;
        head -> next = nn;
        head = nn;
    }
    TypeNode remove () {
        TypeNode* nn= new TypeNode(*tail->next);
        TypeNode* tn = tail-> next;
        delete tail;
        tail=tn;
        return *nn;
    }

        TypeNode* head;
        TypeNode* tail;
};

class Job: public Queue<QueueNode<int>>    {
    /* 
    Derived Queue class of QueueNode<int>
        dependencies:   number of jobs that need to be completed before this job can be executed
        job_id:         job id number
    */ 
    public:
    int dependecies = 0;
    int job_id;
};

class JobQueue: public Queue<QueueNode<Job*>>    {
    // Derived Queue class of QueueNode<Job*>
    public:
    void initialize (int n) {
        // create a queue of n pointers to n Jobs
            for (int i=0; i<n; i++)   {
                Job* newjob = new Job();
                QueueNode<Job*> *jobnode = new QueueNode<Job*>(newjob);
                jobnode->ID->job_id=i;
                insert(*jobnode);
            }
    }
    QueueNode<Job*>* getnode (int job_num)   {
        // return the node of the specific job number
        QueueNode<Job*>* iter = tail;
        while (iter->next->ID->job_id != job_num) {
            iter = iter->next;
        }
        return iter->next;
    }
    void addrule (std::tuple<int, int> rule)    {
        // add a rule of tuple (i,j), where job i depends on job j
        QueueNode<Job*>* dependant = getnode(std::get<0>(rule));
        QueueNode<Job*>* depended = getnode(std::get<1>(rule));
        dependant->ID->dependecies += 1;
        QueueNode<int>* nn=new QueueNode<int>(std::get<0>(rule));
        depended->ID->insert(*nn);
    }
};

class Scheduler    {
    public:
    Scheduler(int n) {
        JobQueue_= JobQueue();
        maxsize = n;
        JobQueue_.initialize(n);
    }
    Queue<QueueNode<int>> readyQueue;
    JobQueue JobQueue_;

    void decreasedependency (int job_num)  {
        // decrease the number of dependencies of Job job_num
        QueueNode<Job*>* jobnode =  JobQueue_.getnode(job_num);
        jobnode -> ID -> dependecies -= 1;
    }
    void schedule() {
        // add Jobs to ReadyQueue as they are available
        while   (readySize != maxsize)  {
            QueueNode<Job*> jobcheck = JobQueue_.remove();
            QueueNode<Job*>* jobcheckptr = &jobcheck;
            if (jobcheckptr->ID->dependecies ==0)  {
                QueueNode<int> *nn = new QueueNode<int>(jobcheckptr->ID->job_id);
                readyQueue.insert(*nn);
                readySize++;
                while (jobcheckptr->ID->tail->next != NULL)    {
                    QueueNode<int> job= jobcheckptr->ID->remove();
                    QueueNode<int>* jobptr= &job;
                    decreasedependency(jobptr->ID);
                }
            }
            else    {
                JobQueue_.insert(*jobcheckptr);
            }
        }
    }
    void executescehdule()  {
        // prints out jobs in scheduled order
        while (readySize != 0  )    {
            QueueNode<int> job = readyQueue.remove();
            QueueNode<int>* jobptr = &job;
            std::cout<<jobptr->ID<<" , ";
            readySize--;
        }
        std::cout<<std::endl;
    }
    private:
    int maxsize;
    int readySize=0;
    
};

int main(int argc, char* argv[])  {
    Scheduler test=Scheduler(5);
    test.JobQueue_.addrule(std::make_tuple(1,3));
    test.JobQueue_.addrule(std::make_tuple(1,2));
    test.JobQueue_.addrule(std::make_tuple(2,4));
    test.JobQueue_.addrule(std::make_tuple(0,1));
    test.schedule();
    test.executescehdule();

    int n=30;
    Scheduler test2=Scheduler(n);
    std::cout<<"Randomizing "<<n-1<<" rules:"<<std::endl;
    for (int i=0; i<n-1; i++)  {
        std::tuple<int, int> rule =  RNGtuple(n);
        std::cout<<std::get<0>(rule)<<","<<std::get<1>(rule)<<std::endl;
        test2.JobQueue_.addrule(rule);
    }
    test2.schedule();
    test2.executescehdule();

}