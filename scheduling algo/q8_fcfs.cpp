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

void FIFS(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int tb_time = 0;
    for(int i = 0;i<total;i++)
    {
                tb_time += a[i].Burst_Time;
                a[i].TurnAround_Time =  tb_time - a[i].Arrival_Time;
                a[i].Waiting_Time = a[i].TurnAround_Time - a[i].Burst_Time;

        *avg_ttime = *avg_ttime +  a[i].TurnAround_Time;
        *avg_wtime = *avg_wtime + a[i].Waiting_Time;
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
     cout<<" FIFS (First In First Serve)"<<endl;

                FIFS(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);

}
