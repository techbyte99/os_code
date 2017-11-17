#include<iostream>
using namespace std;

struct hole
{
    int hole_size;
    bool check;
    int internal;
};

struct Difference
{
    int difference;
    int number;
};


bool first_fit(hole *blocks,int n_blocks,int hole_size,int *fragmentation,int *hole_number)
{
    bool is_allocated = false;

    for(int i = 0;i<n_blocks;i++)
    {
            if(blocks[i].hole_size>hole_size && blocks[i].check == false)
            {
                blocks[i].internal = blocks[i].hole_size - hole_size;
                *fragmentation = blocks[i].internal;
                blocks[i].check = true;
                *hole_number = blocks[i].hole_size;

                is_allocated = true;
                break;
            }
    }

    return is_allocated;
}

bool external_frag(hole *blocks,int n_blocks,int* fragmentation)
{
    bool is_fragment = false;

    for(int i = 0;i<n_blocks;i++)
    {
        if(blocks[i].check == false)
        {
            *fragmentation = *fragmentation + blocks[i].hole_size;
            is_fragment = true;
        }
    }
    return is_fragment;
}

int main()
{
    int n_blocks = 0,n_process = 0,temp = 0;
cout<<"Enter number of blocks(holes)"<<endl;
    cin>>n_blocks;

    struct hole blocks[n_blocks];
    cout<<endl<<"Enter size(bytes) of each block(hole)"<<endl;

    for(int i = 0;i<n_blocks;i++)
    {
        cout<<endl<<"Enter size of block(hole) "<<i+1<<endl;
        cin>>blocks[i].hole_size;
        blocks[i].check = false;
        blocks[i].internal = 0;
    }

    cout<<endl<<"Enter number of Processes"<<endl;
    cin>>n_process;
    int Process[n_process];
    cout<<endl<<"Enter size(bytes) of each Process"<<endl;

    for(int i = 0;i<n_process;i++)
    {
         cout<<endl<<"Enter size of Process "<<i+1<<endl;
         cin>>Process[i];
    }

    int fragmentation = 0,hole_number = 0;
            bool is_allocated = false;

            for(int i = 0;i<n_process;i++)
            {
                    fragmentation = 0;
                    hole_number = 0;
                    is_allocated = false;
                    is_allocated = first_fit(blocks,n_blocks,Process[i],&fragmentation,&hole_number);

                    if(is_allocated == true)
                    {
                        cout<<endl<<"Process "<<i+1<<" is allocated to hole of size  "<<hole_number<<" bytes"<<endl;
                        cout<<endl<<"Internal Fragmentation is = "<<fragmentation<<endl;
                    }
                    else
                    {
                        bool is_frag = false;
                        cout<<endl<<"Cannot allocate the Process "<<i+1<<endl;

                        is_frag = external_frag(blocks,n_blocks,&fragmentation);

                        if(is_frag == true)
                        {
                            cout<<" due to External Fragmentation"<<endl<<" External Fragmentation is = "<<fragmentation<<" bytes"<<endl;
                        }
                        else
                        {
                            cout<<" all blocks(holes) are allocated"<<endl<<" External Fragmentation is = "<<fragmentation<<"bytes"<<endl;
                        }
                    }
            }
}
