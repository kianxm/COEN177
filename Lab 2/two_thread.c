// Name: Kian Malakooti
// Date: Sept 28, 2022 
// Title: Lab2 – Programming in C and use of Systems Calls 
// Description: Step 6: Two threads

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>    /* threads */

void *thread1(void *n) {
    for(int i = 0; i < 100; i++) {
        printf("\t \t \t Thread 1 %d\n", i);
        usleep(*((int *) n)); //typecast void -> int -> deref
    }
    pthread_exit((void *)n);
}

void *thread2(void *n) {
    for(int j = 0; j < 100; j++) {
        printf("\t \t \t Thread 2 %d\n", j);
        usleep(*((int *) n)); //typecast void -> int -> deref
    }
    pthread_exit((void *)n);
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    int i, n = atoi(argv[1]);
    int *arg = malloc(sizeof(*arg)); // memory allocation for delay
    *arg = n;
    printf("\n Before threading.\n");

    pthread_create(&t1, NULL, thread1, arg);
    pthread_create(&t2, NULL, thread2, arg);
    pthread_join(t1, (void **)&arg);
    pthread_join(t2, (void **)&arg);
    free(arg); // free memory
    return 0;
}