#include <iostream>

struct QueueNode    {
    int ID;
    QueueNode* next;
    QueueNode (int i) : next(NULL)   {
        ID=i;
    };
};

class CircleQueue {
    public:
    CircleQueue(int n) {
        QueueNode* start = new QueueNode(0);
        head = start;
        head->next = head;
        tail = start;
        for (int i=n-1; i>0; i--)   {
            QueueNode *adder = new QueueNode(i);
            insert(*adder);
            if (i==n-1)    {
                judge = head;
            }
        }
        tail->next=head;
    }
    void insert(QueueNode& node)    {
        QueueNode* nn = new QueueNode(node);
        nn-> next = head;
        head = nn;
        std::cout<<nn->ID<<" is the next to "<<nn->next->ID<<std::endl;
    }
    void move(int m)    {
        for (int i=0; i<m-1; i++)   {
            judge = judge->next;
            std::cout<<"Judge is the at "<<judge->ID<<std::endl;
        }
    }
    QueueNode remove () {
        QueueNode nn(*judge->next);
        QueueNode* jn = judge-> next-> next;
        delete judge->next;
        judge->next=jn;
        return nn;
    }
    void printRemove(QueueNode node)    {
        std::cout<<"Node "<<node.ID<<" has been removed."<<std::endl;
    }
    void printWin()    {
        std::cout<<"Node "<<judge->ID<<" is the last remaining."<<std::endl;
    }
    QueueNode startGame (int m) {
        std::cout<<judge->ID<<" is the next to "<< judge->next->ID<<std::endl;
        while (judge-> next != judge) {
            move(m);
            QueueNode x =remove();
            printRemove(x);
        }
        printWin();
        return *judge;
    }

    private:
        QueueNode* head;
        QueueNode* tail;
        QueueNode* judge;
};

int main(int argc, char* argv[])
{
    if (argc != 3)   {
        printf("Error, wrong number of arguments\n");
        exit(1);
    }
    std::string s1= argv[1];
    std::string s2= argv[2];
    bool has_only_digits = (s1.find_first_not_of( "0123456789" ) == std::string::npos);
    bool has_only_digits2 = (s2.find_first_not_of( "0123456789" ) == std::string::npos);
    if (!has_only_digits || !has_only_digits2)   {
        printf("Error, argument is not a nonzero integer\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    CircleQueue game = CircleQueue(n);
    game.startGame(m);
    return 0;
}