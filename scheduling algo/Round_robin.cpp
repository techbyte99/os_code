#include<iostream>
using namespace std;

struct Process
{
    char P_name;
    int Burst_Time;
    int Arrival_Time;
    int Waiting_Time;
    int TurnAround_Time;
    int Priority;
    bool check;
    int Remaining_Time;
};

void get_details(struct Process a[],int total)
{
    cout<<endl<<" Enter details of each process"<<endl;
    for(int i=0;i<total;i++)
    {
        cout<<endl<<" Enter details for "<<i+1<<" Process "<<endl;
        cout<<endl<<" Enter name of Process"<<endl;
        cin>>a[i].P_name;

        cout<<endl<<" Enter Burst Time "<<endl;
        cin>>a[i].Burst_Time;
        a[i].Remaining_Time = a[i].Burst_Time;

        cout<<endl<<" Enter Priority "<<endl;
        cin>>a[i].Priority;

        cout<<endl<<" Enter Arrival Time "<<endl;
        cin>>a[i].Arrival_Time;

        a[i].TurnAround_Time = a[i].Waiting_Time = 0;

        a[i].check = false;

    }
}

void display(struct Process *a,int total)
{
    cout<<endl<<"Process Name"<<"  Burst Time"<<"  Arrival Time"<<"  Priority"<<"  TurnAround Time"<<"  Waiting Time"<<endl<<endl;
    for(int i=0;i<total;i++)
    {
      cout<<a[i].P_name<<"\t          "<<a[i].Burst_Time<<"\t    "<<a[i].Arrival_Time<<"\t\t "<<a[i].Priority<<"\t    "<<a[i].TurnAround_Time<<"\t\t\t"<<a[i].Waiting_Time<<endl;
    }

}

void Round_Robin(struct Process a[],int total,float *avg_ttime,float *avg_wtime,int time_quantum)
{
    int range = 0,select_store = 0,tb_time = 0,checked = 0,select_main = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[select_store].P_name)
                select_main = i;
        }

        if(a[select_main].Remaining_Time > 0)
        {
            a[select_main].Remaining_Time = a[select_main].Remaining_Time - time_quantum;

            if(a[select_main].Remaining_Time < 0)
            {
                tb_time = tb_time + time_quantum + a[select_main].Remaining_Time;
                a[select_main].Remaining_Time = 0;
                range = tb_time;
            }
            else
            {
                tb_time += time_quantum;
                range += time_quantum;
            }
        }
        if(a[select_main].Remaining_Time == 0)
        {
            a[select_main].check = true;
            executed++;
            checked++;

            a[select_main].TurnAround_Time =  tb_time - a[select_main].Arrival_Time;
            a[select_main].Waiting_Time = a[select_main].TurnAround_Time - a[select_main].Burst_Time;

            *avg_ttime = *avg_ttime +  a[select_main].TurnAround_Time;
            *avg_wtime = *avg_wtime +  a[select_main].Waiting_Time;

            select_store--;
        }

        select_store++;
        if(select_store == total-checked)
            select_store = 0;
    }
    return;
}

int main()
{
int total;
    float avg_ttime = 0, avg_wtime = 0;
    cout<<"Enter total number of Processes "<<endl;
    cin>>total;

    Process scheduler[total];

    get_details(scheduler,total);
     int time_quantum = 0;
                cout<<endl<<"Enter Quantum or Time-Slot "<<endl;
                cin>>time_quantum;
    cout<<"  Round-Robin"<<endl;

     Round_Robin(scheduler,total,&avg_ttime,&avg_wtime,time_quantum);
     display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);

}
