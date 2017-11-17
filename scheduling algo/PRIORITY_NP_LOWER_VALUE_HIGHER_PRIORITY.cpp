
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

void swap_struct(struct Process *temp,struct Process *temp1)
{
    char P_name;
    int Burst_Time,Arrival_Time,Waiting_Time,TurnAround_Time,Priority,Remaining_Time;
    bool check;

      P_name = temp->P_name ;
      Burst_Time = temp->Burst_Time;
      Arrival_Time = temp->Arrival_Time;
      Waiting_Time = temp->Waiting_Time;
     TurnAround_Time = temp->TurnAround_Time;
     Priority = temp->Priority;
     check = temp->check;
     Remaining_Time = temp->Remaining_Time;

     temp->P_name =  temp1->P_name;
     temp->Burst_Time = temp1->Burst_Time;
     temp->Arrival_Time  = temp1->Arrival_Time;
     temp->Waiting_Time = temp1->Waiting_Time;
     temp->TurnAround_Time = temp1->TurnAround_Time;
     temp->Priority = temp1->Priority;
     temp->check = temp1->check;
     temp->Remaining_Time = temp1->Remaining_Time;

     temp1->P_name = P_name;
     temp1->Burst_Time = Burst_Time;
     temp1->Arrival_Time  = Arrival_Time;
     temp1->Waiting_Time = Waiting_Time;
     temp1->TurnAround_Time = TurnAround_Time;
     temp1->Priority = Priority;
     temp1->check = check;
     temp1->Remaining_Time = Remaining_Time;

}

void sorted_priority(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Priority>a[j].Priority)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

void NP_Priority(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int range = 0,select = 0,tb_time = 0,executed = 0;
    Process store[total];

    while(executed != total)
    {
        int eligible = 0;

        for(int i = 0;i<total;i++)
        {
            if(a[i].Arrival_Time <= range && a[i].check == false)
            store[eligible++] = a[i];
        }

        sorted_priority(store,eligible);
        range += store[0].Burst_Time;

        for(int i = 0;i<total;i++)
        {
            if(a[i].P_name == store[0].P_name)
                select = i;
        }

        a[select].check = true;
        executed++;

        tb_time += a[select].Burst_Time;
        a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
        a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

        *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
        *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

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
    cout<<" Non-Preemptive Priority Based "<<endl;

                NP_Priority(scheduler,total,&avg_ttime,&avg_wtime);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
}

