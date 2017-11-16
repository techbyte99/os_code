#include<iostream>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>

using namespace std;

#define SIZE 30
#define READ 0
#define WRITE 1

int main()
{
    int fd[2],pid;
    char write_message[SIZE],read_message[SIZE];

    if(pipe(fd) == -1)
    {
        cerr<<" Internal error occured  at pipe";
        exit(1);
    }
    else
    {
            pid = fork();

            if(pid<0)
            {
                cerr<<" ERROR !!!  Cannot create child process"<<endl;
                exit(1);
            }
            else if(pid > 0)
            {
                wait(NULL);
                close(fd[WRITE]);

                    cout<<endl<<"  In Parent Process "<<endl;
					cout<<endl<<"Data retrieved from child process is:"<<endl;
                    read(fd[READ],read_message,SIZE-1);
                    cout<<read_message<<endl;

                close(fd[READ]);
            }
            else if(pid == 0)
            {

                close(fd[READ]);

                    cout<<endl<<"  In Child Process "<<endl<<" Enter the data to be sent to the parent process : ";
                    cin.getline(write_message,SIZE - 1);

                   write(fd[WRITE],write_message,SIZE-1);

                close(fd[WRITE]);
            }
    }
}
