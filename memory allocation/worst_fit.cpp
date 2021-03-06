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

Difference select_hole_worst(Difference *a,int length)
{

    //sort the array
    for(int i = 0;i<length;i++)
    {
        for(int j = i+1;j<length;j++)
        {
            if(a[i].difference <  a[j].difference)
            {
                int t1 ,t2;
                t1 = a[i].difference;
                t2 = a[i].number;

                a[i].difference = a[j].difference;
                a[i].number = a[j].number;

                a[j].difference = t1;
                a[j].number = t2;
            }
        }
    }

    return a[0];
}

bool worst_fit(hole *blocks,int hole_size,int n_blocks,int *a,int *fragmentation,int *hole_number)
{

     Difference store[n_blocks],selected_hole;
    int j = 0;

     //create array
       for(int i = 0;i<n_blocks;i++)
     {
        if(blocks[i].check == false)
        {
          store[j].difference = blocks[i].hole_size-hole_size;
          store[j].number = blocks[i].hole_size;
          j++;
        }
     }

     selected_hole = select_hole_worst(store,j);

        //if there is no suitable hole return
     if(selected_hole.difference < 0 )
     return false;

     j = 0;
            //select the hole from blocks array
        for(int i = 0;i<n_blocks;i++)
            {
                if(blocks[i].hole_size == selected_hole.number)
                j = i;
            }
                blocks[j].internal = blocks[j].hole_size - hole_size;
                blocks[j].check = true;
                *fragmentation = blocks[j].internal;
                *hole_number = blocks[j].hole_size;

     return true;
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
                    is_allocated = worst_fit(blocks,Process[i],n_blocks,Process,&fragmentation,&hole_number);

                    if(is_allocated == true)
                    {
                        cout<<endl<<"Process "<<i+1<<" is allocated to hole of size  "<<hole_number<<" bytes"<<endl;
                        cout<<endl<<"Internal Fragmentation is = "<<fragmentation<<endl;
                    }
                    else
                    {
                        bool is_frag = false;
                        cout<<endl<<"Cannot allocate the Process "<<i+1;

                        is_frag = external_frag(blocks,n_blocks,&fragmentation);

                        if(is_frag == true)
                        {
                            cout<<" due to External Fragmentation"<<endl<<" External Fragmentation is = "<<fragmentation;
                        }
                        else
                        {
                            cout<<" all blocks(holes) are allocated"<<endl<<" External Fragmentation is = "<<fragmentation;
                        }
                    }
            }

}
