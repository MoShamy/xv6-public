/*
The purpose of this user program is to test the getppid() system call.
This is done  by fork() creating a new child, and having each process identify its fork() value, pid and PPID
Implemented by Mostafa Elshamy
*/

#include "types.h"
#include "stat.h"
#include "user.h"


void printHeader(char *header){ //utility funciton for header printing --mostafa
    printf(1,"\n\n\n---------------------------------%s---------------------------------\n\n\n",header);
}
void main(){

    int given_pid  = fork(); // child executes from here again
    int pid = getpid();
    int ppid = getppid();

    if(ppid == 0){ //Detect when a process has no parent (orphan) and derminate --mostafa
        printf(1,"Get PPID system call failed.\nParent process may not exist!\n");
        exit();
    }

    char *childHeader = "Child Process";
    char *parentHeader = "Parent Process";

    if(given_pid<0){ //failed
        printf(1,"Fork Failed: womp womp"); //make sure that the fork didnt fail --mostafa
        exit();
    }else if(given_pid == 0){ //child
        printHeader(childHeader);
        printf(1,"The fork() function assigned me a PID: %d.\n",given_pid);
        printf(1,"My actual PID: %d\n",pid);
        printf(1,"My PPID: %d",ppid); //testing my new system call on the child --mostafa
    }else{ //parent
        wait();
        printHeader(parentHeader);
        printf(1,"The fork() function assigned me a PID: %d.\n//This should represent the PID of the child process\n",given_pid);
        printf(1,"My PID: %d\n",pid);
        printf(1,"My PPID: %d\n",ppid); //testing my new system call on the parent --mostafa

    }

    exit();
}