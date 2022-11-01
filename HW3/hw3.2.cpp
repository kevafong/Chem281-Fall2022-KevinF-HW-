#include <iostream>
#include <list>
#include <string>
#include <algorithm>


void print_list(std::list<int> seq)  {
    std::cout<<"[ ";
    for (int x : seq)
        std::cout << x << " ";
    std::cout<<"]"<<std::endl;
}

void print_lol(std::list<std::list<int>> seqs)  {
    for (std::list<int> x : seqs)
        print_list(x);
}

std::list<std::list<int>> sequence(int n, int i)   {
// creates lists of non increasing sequences of sum n, where the largest possible number is i
    if (i>n)    {
        i=n;
    }
    std::list<std::list<int>> seqslist;
    if (n==i) {
        std::list<int> seq(1, n);
        seqslist.push_back(seq);
        i--;
    }
    while (i>0) {
        std::list<std::list<int>> subseqs= sequence(n-i, i);
        std::list<std::list<int>> subseqs2 ;
        for (std::list<int> seq:subseqs)    {
            seq.push_front(i);
            subseqs2.push_back(seq);
        }
        seqslist.splice(seqslist.end(), subseqs2);
        i--;
    }
    return seqslist;
    
}

int main(int argc, char* argv[])
{
    if (argc < 2)   {
        printf("Error, argument missing\n");
        exit(1);
    }
    if (argc > 2)   {
        printf("Error, too many arguments\n");
        exit(1);
    }
    std::string s= argv[1];
    bool has_only_digits = (s.find_first_not_of( "0123456789" ) == std::string::npos);
    if (!has_only_digits)   {
        printf("Error, argument is not a nonzero integer\n");
        exit(1);
    }
    int input = atoi(argv[1]);
    std::list<std::list<int>> seqs= sequence(input, input);
    print_lol(seqs);
    return 0;
}