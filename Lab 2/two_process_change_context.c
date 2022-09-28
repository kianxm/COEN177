// Name: Kian Malakooti
// Date: Sept 28, 2022 
// Title: Lab2 – Programming in C and use of Systems Calls 
// Description: Step 7: Two process change context

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 

int main() {
    pid_t pid;
    printf("Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }    
    else if(pid == 0)
    {
        execlp("/bin/ls", "ls", NULL);
    }
    else
    {
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
    return 0;
}


