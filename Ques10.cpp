#include<iostream>
using namespace std;

void create_table(int *a,int t_size)
{
    a[0] = 0;
    for(int i = 0;i<t_size;i++)
    {
        if(i == 0)
        a[i] = 2;
        else
        a[i] = a[i-1] + 2;
    }
}

void display_table(int *a,int t_size)
{
    cout<<endl<<"Page Table is :--"<<endl;
    cout<<endl<<" Page No  Frame No"<<endl<<endl;;

    for(int i = 0;i<t_size;i++)
    cout<<"   "<<i<<"       "<<a[i]<<endl;
}

int calculate(int *a,int p_number,int offset,int t_size,int p_size)
{
    if(p_number >=0 && p_number <t_size)
    {
        if(offset >=0 && offset <p_size)
        {
            return (a[p_number]*p_size+offset);
        }
        else
        {
            cout<<endl<<"Wrong offset entered : "<<endl;
            return -2;
        }
    }
    else
    {
        cout<<endl<<"Wrong page number entered : "<<endl;
        return -1;
    }
}

int main(void)
{
    int p_number = 0,offset = 0,p_add = 0,p_size = 0,lm_size = 0,t_size = 0;
    char ch;

    cout<<endl<<"Enter Page Size (in bytes) : ";
    cin>>p_size;
    cout<<endl<<"Enter Logical Memory Size (in bytes) : ";
    cin>>lm_size;

    t_size = lm_size/p_size;
    int p_table[t_size];

    cout<<endl<<"Total number of Pages = "<<t_size<<endl;
    cout<<endl<<"Total number of Frames = "<<t_size + 10<<endl;

    cout<<endl<<"Frame Size = "<<p_size<<" bytes"<<endl;


    create_table(p_table,t_size);
    display_table(p_table,t_size);

    do
  {
    cout<<endl<<"Enter Logical Address : ";

    cout<<endl<<"Enter Page Number : ";
    cin>>p_number;
    cout<<endl<<"Enter Offset : ";
    cin>>offset;

    cout<<endl<<"Phsical Address is  = "<<calculate(p_table,p_number,offset,t_size,p_size);
    cout<<endl<<"Press y/Y to continue"<<endl;
    cin>>ch;
    }
    while(ch == 'y'|| ch == 'Y');
}
