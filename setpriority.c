#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


//this function tests the set priority syscall

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf(1, "Usage: setpriority pid priority\n");
        exit();
    }

    int pid = atoi(argv[1]);
    int priority = atoi(argv[2]);

    int old_priority = setpriority(pid, priority);
    if (old_priority == -1) {
        printf(1, "Process with PID %d not found.\n", pid);
    } else {
        printf(1, "Old priority of process %d was %d. New priority is %d.\n", pid, old_priority, priority);
    }

    exit();

}