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
    int Remaining_Time;
};

void get_details(struct Process a[],int total)
{
    cout<<endl<<" ENTER DETAILS OF EACH PROCESS  :"<<endl;
    cout<<"============================================\n";
    for(int i=0;i<total;i++)
    {
        cout<<endl<<" Enter details for "<<i+1<<" Process "<<endl;
        cout<<endl<<" Enter name of Process : ";
        cin>>a[i].P_name;

        cout<<endl<<" Enter Burst Time  : ";
        cin>>a[i].Burst_Time;
        a[i].Remaining_Time = a[i].Burst_Time;

        cout<<endl<<" Enter Priority  : ";
        cin>>a[i].Priority;

        cout<<endl<<" Enter Arrival Time  : ";
        cin>>a[i].Arrival_Time;

        a[i].TurnAround_Time = a[i].Waiting_Time = 0;

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

      P_name = temp->P_name ;
      Burst_Time = temp->Burst_Time;
      Arrival_Time = temp->Arrival_Time;
      Waiting_Time = temp->Waiting_Time;
     TurnAround_Time = temp->TurnAround_Time;
     Priority = temp->Priority;
     Remaining_Time = temp->Remaining_Time;

     temp->P_name =  temp1->P_name;
     temp->Burst_Time = temp1->Burst_Time;
     temp->Arrival_Time  = temp1->Arrival_Time;
     temp->Waiting_Time = temp1->Waiting_Time;
     temp->TurnAround_Time = temp1->TurnAround_Time;
     temp->Priority = temp1->Priority;
     temp->Remaining_Time = temp1->Remaining_Time;

     temp1->P_name = P_name;
     temp1->Burst_Time = Burst_Time;
     temp1->Arrival_Time  = Arrival_Time;
     temp1->Waiting_Time = Waiting_Time;
     temp1->TurnAround_Time = TurnAround_Time;
     temp1->Priority = Priority;
     temp1->Remaining_Time = Remaining_Time;

}

void sorted_burst_time(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Burst_Time>a[j].Burst_Time)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
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

void SJF_NP(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int select = 0,tb_time = 0,executed = 0;

    while(executed != total)
    {
        sorted_burst_time(a,total);

        executed++;
        tb_time += a[select].Burst_Time;
        a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
        a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

        *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
        *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

        select++;

    }
    return;
}

void sorted_remaining_time(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Remaining_Time>a[j].Remaining_Time)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

void SRTF(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int select = 0,tb_time = 0,executed = 0;

    while(executed != total)
    {
        sorted_remaining_time(a,total);

        a[select].Remaining_Time = a[select].Remaining_Time - 1;
        tb_time += 1;

        if(a[select].Remaining_Time == 0)
       {
            executed++;

            a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
            a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

            *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
            *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

            select++;
        }
    }

    return;
}

void sorted_priority(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].Priority<a[j].Priority)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

void NP_Priority(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int select = 0,tb_time = 0,executed = 0;

    while(executed != total)
    {
        sorted_priority(a,total);
        executed++;

        tb_time += a[select].Burst_Time;
        a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
        a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

        *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
        *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

        select++;

    }
    return;
}

void P_Priority(struct Process a[],int total,float *avg_ttime,float *avg_wtime)
{
    int select = 0,tb_time = 0,executed = 0;

    while(executed != total)
    {
        sorted_priority(a,total);

        a[select].Remaining_Time = a[select].Remaining_Time - 1;
        tb_time += 1;

        if(a[select].Remaining_Time == 0)
       {
            executed++;

            a[select].TurnAround_Time =  tb_time - a[select].Arrival_Time;
            a[select].Waiting_Time = a[select].TurnAround_Time - a[select].Burst_Time;

            *avg_ttime = *avg_ttime +  a[select].TurnAround_Time;
            *avg_wtime = *avg_wtime +  a[select].Waiting_Time;

            select++;
        }
    }

    return;
}

void Reset(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {   a[i].TurnAround_Time = 0;
        a[i].Waiting_Time = 0;
        a[i].Remaining_Time = a[i].Burst_Time;
    }
}

void restore(struct Process a[],int total)
{
    for(int i = 0;i<total;i++)
    {
        for(int j = i+1;j<total;j++)
        {
            if(a[i].P_name>a[j].P_name)
            {
                swap_struct(&a[i],&a[j]);
            }
        }
    }
    return;
}

int main()
{
    char option ,key;
    int total;
    float avg_ttime = 0, avg_wtime = 0;
    cout<<"               SCHEDULING ALGORITHM IMPLEMENTATION \n";
    cout<<"Enter total number of Processes  : ";
    cin>>total;
    cout<<endl<<"Note : Highest the Number, High will be it's Priority"<<endl;
    cout<<" Note : Arrival time of the processes are assumed to be 0 \n";

    Process scheduler[total];

    get_details(scheduler,total);

    do
    {
         cout<<"\n================================================\n";
        cout<<endl<<"                               M E N U  "<<endl<<endl;
        cout<<" 1. FCFS (First Come First Serve)"<<endl;
        cout<<" 2. SJF (Shortest Job First) Non-Preemptive"<<endl;
        cout<<" 3. SRTF (Shortest Remaining Time First)"<<endl;
        cout<<" 4. Non-Preemptive Priority Based "<<endl;
        cout<<" 5. Preemptive Priority Based "<<endl;
        cout<< "Enter your choice : ";
        cin>>option;
        switch(option)
        {
            case 1:
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                FIFS(scheduler,total,&avg_ttime,&avg_wtime);
                 restore(scheduler,total);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
                break;
                case 2:
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                SJF_NP(scheduler,total,&avg_ttime,&avg_wtime);
                 restore(scheduler,total);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 3:
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                SRTF(scheduler,total,&avg_ttime,&avg_wtime);
                 restore(scheduler,total);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 4:
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                NP_Priority(scheduler,total,&avg_ttime,&avg_wtime);
                 restore(scheduler,total);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is : "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is : "<<(avg_ttime/total);
            }
            break;
            case 5:
            {
                Reset(scheduler,total);
                avg_ttime = 0, avg_wtime = 0;

                P_Priority(scheduler,total,&avg_ttime,&avg_wtime);
                 restore(scheduler,total);
                display(scheduler,total);

                cout<<endl<<" Average Waiting Time is  :  "<<(avg_wtime/total);
                cout<<endl<<" Average TurnAround Time is  :  "<<(avg_ttime/total);
            }
            break;
            default:
                cout<<endl<<" Wrong choice enter , try again !!!!"<<endl;
        }
        cout<<endl<<" Press y,to continue : ";
        cin>>key;
    }
    while(key== 'y' || key == 'Y');
}

