#include<iostream>
using namespace std;

#define MAX_SIZE 10
class Queue_circular
{
    public:

    int out,in;
    int container[MAX_SIZE];

    void create_empty_queue()
    {
        this->out = -1;
        this->in = -1;
    }

    bool is_full()
    {
        if(this->out == (this->in + 1)%MAX_SIZE)
        return true;
        else
        return false;
    }

    bool is_empty_()
    {
        if(this->out == -1 && this->in == -1 )
        return true;
        else
        return false;
    }

    void enqueue(int element)
    {
        if(this->is_full() == false)
        {
            if(this->out == -1&&this->in == -1)
            {
                this->out =0;
                this->in = 0;
                this->container[this->in] = element;
            }
            else
            {
                this->in = (this->in + 1)%MAX_SIZE;
                this->container[this->in] = element;
            }
        }
        else
        cout<<endl<<"Sorry cannot produce element,  buffer is full"<<endl;

    }

    void dequeue()
    {
        if(this->is_empty_() == false)
        {
            if(this->out == this->in && this->is_full() == false)
            {
                cout<<endl<<this->container[this->out];
            this->out = this->in = -1;
            }
            else
            {
                cout<<endl<<this->container[this->out];
                this->out = (this->out + 1)%MAX_SIZE;
            }
        }
        else
        {
            cout<<endl<<"Cannot consume, BUFFER do not contain any element"<<endl;
        }
    }

    void display_queue()
    {
        if(this->is_empty_() == false)
        {
            cout<<endl<<" Elements in the buffer are : "<<endl;
            for(int i = this->out ; i<= this->in;i++)
                cout<<this->container[i]<<"  ";
        }
        else
        {
            cout<<endl<<" Buffer is empty"<<endl;
        }
    }
};


int main(void)
{
    char  ch;
	int option;
    Queue_circular q;
    q.create_empty_queue();
    do
    {
        cout<<"                  CIRCULAR QUEUE IMPLEMENTATION\n"; 
         cout<< "       MENU  \n"         ;
        cout<<"1. INSERT/produce an element in buffer"<<endl;
        cout<<"2. DELETE/consume an element from buffer"<<endl;
        cout<<"3. Display the elements of the buffer"<<endl;
		cout<<endl<<" Enter an option : ";
        cin>>option;

        switch(option)
        {
            case 1:
            {
                int element;
                cout<<endl<<"Enter the element : ";
                cin>>element;
                q.enqueue(element);

            }
            break;
            case 2:
            {
                q.dequeue();
            }
            break;
            case 3:
            {
                q.display_queue();
            }
            break;
            default:
            cout<<endl<<" Wrong option selected "<<endl;

        }
        cout<<endl<<" Press y, to continue"<<endl;
        cin>>ch;
    }
    while(ch == 'y'|| ch == 'Y');

}
