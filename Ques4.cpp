#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void SameProgram();
void DiffProgram();
void DiffCode();
void Waitcall();

int main(void)
{
    int key;

    cout << "\t Parent and child implementation" << endl;
    cout<< "                M E N U \n";
    cout << "1. Same program with same code" << endl;
    cout << "2. Same program with different code" << endl;
    cout << "3. Different Programs (with no wait )" << endl;
    cout << "4. Parent with wait call" << endl ;
    cout << "Enter your choice : ";
    cin >> key;

    switch(key) {
        case 1:
            SameProgram();
            break;

        case 2:
            DiffCode();
            break;

        case 3:
            DiffProgram();
            break;

        case 4:
            Waitcall();
            break;

        default:
            cout << endl << "Wrong Choice!!!" << endl;
            exit(1);
     }

}


void SameProgram()
{

    int pid = fork();


    int m_pid = getpid();


    int p_pid = getppid();

	if (pid < 0) {
        cout << endl << "fork() failed" << endl;
        exit(-1);
    }


    cout << endl << "My pid is : " << m_pid << endl;
    cout << endl << "My parent pid is : " << p_pid << endl;

    return;
}


void DiffCode()
{
    int pid = fork();

    if (pid < 0) {
        cout << endl << "fork() failed.";
        exit(-1);
    }

    else if (pid > 0) {
        cout << endl << "\tInside Parent";
		cout << endl << " child pid : " << pid;
        cout << endl << "own pid : " << getpid() << endl;
    }

    else {
        cout << endl << "\tInside Child";
		cout << endl << " my pid is : " << getpid();
        cout << endl << "parent pid is : " << getppid() << endl;
    }
}


void DiffProgram()
{
    int pid = fork();

    if (pid < 0) {
        cout << endl << "fork() failed.";
        exit(-1);
    }

    else if(pid > 0) {
        cout << endl << "\tInside Parent";
		cout << endl << "pid : " << pid;
        cout << endl << "Parent pid : " << getpid() << endl;
    }

    else {
        cout << endl << "\tInside Child" << endl;
        cout << endl << "pid : " << pid;
        cout << endl << "Parent pid : " << getpid() << endl;

        execlp("/bin/ls", "ls", "-l", (char *) NULL);

        cout << endl << "Child pid is : " << getpid() << endl;
    }
}


void Waitcall()
{
    int pid = fork();

    if (pid < 0) {
        cout << endl << "fork() call failed.";
        exit(-1);
    }

    else if (pid > 0) {
		int pid1 = getpid();

		cout << endl << "\tInside Parent";
		cout << endl << "Wait() system called" << endl;

        // call wait
        wait(NULL);

        cout << endl << "\tResume Parent ";
        cout << endl << "Parent pid: " << pid1 << endl;
    }

    else {
        cout << endl << "\tInside Child ";

		cout << endl << "pid : " << pid;
		cout << endl << "Child pid : " << getpid() << endl;
    }
}
