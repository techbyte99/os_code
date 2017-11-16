#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void display_permission(mode_t buffer)
{
    cout<<"Owner access permissions is :  ";

    if(S_IREAD!=0)
    cout<<"r";
    else
    cout<<"-";
    if(S_IWRITE!=0)
    cout<<"w";
    else
    cout<<"-";
    if(S_IEXEC!=0)
    cout<<"x";
    else
    cout<<"-";
}

int main(int argv,char* argvs[])
{
    if(argv == 1)
    {
        cout<<" Please enter atleast 1 file_name"<<endl;
        return 1;
    }

    struct stat buffer;

    for(int i = 1;i< argv;i++)
    {
        cout<<endl<<" For file "<<argvs[i]<<endl;
        if(stat(argvs[1],&buffer )== 0)
        {
            display_permission(buffer.st_mode);
            cout<<endl<<"File's last access time is :  "<<ctime(&buffer.st_atim.tv_sec) <<endl;
        }
        else
        {
            cout<<endl<<"stat function do not work properly"<<endl;
            exit(1);
        }
    }
}
