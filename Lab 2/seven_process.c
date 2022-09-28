// Name: Kian Malakooti
// Date: Sept 28, 2022 
// Title: Lab2 – Programming in C and use of Systems Calls 
// Description: Step 5: 7 processes

#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); // 1st child
    pid2 = fork(); // 2nd child, 1st child -> 1 grandchild 

    if (pid1 > 0 && pid2 > 0)
        printf("Parent ID: %d\n", getpid()); 
    if (pid1 == 0 && pid2 > 0) { // 1st child of parent
        printf("Child ID: %d & Parent ID: %d\n", getpid(), getppid());
        pid2 = fork(); // 2nd child -> 2nd grandchildren
    }
    if (pid1 > 0 && pid2 == 0) { // 2nd child of parent
        printf("Child ID: %d & Parent ID: %d\n", getpid(), getppid());
        pid1 = fork(); // 1st child of 2nd child of parent
        if (pid1 > 0) { // still on 2nd child
            pid2 = fork(); // 2nd child of 2nd child of parent
            pid1 = 0;
        }
    }
    if (pid1 == 0 && pid2 == 0) {
        printf("Child ID: %d & Parent ID: %d\n", getpid(), getppid()); 
    }

    return 0;
}