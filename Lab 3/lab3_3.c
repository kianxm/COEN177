// Name: Kian Malakooti
// Date: October 5, 2022 
// Title: Lab3 – Pthreads and inter-process Communication – Pipes
// Description: Step 3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main(int argc, char *argv[])
{
	int fds[2];
	char buff[60];
	int count;
	int i;
	pipe(fds);

	if(fork() == 0) {
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
		dup2(fds[1], 1); //fds[1] = upstream end of pipe
		close(fds[0]); //closes downstream end of pipe
		execlp("ls", "ls", 0);
		exit(0);
	} else if(fork() == 0) {
		printf("\nReader on the downstream end of the pipe \n");
		close(fds[1]); //closes upstream end of pipe
		while((count = read(fds[0], buff, 60)) > 0) { //fds[0] = downstream end of pipe
			for(i = 0; i < count; i++) {
				write(1, buff+i, 1); //writes buffer to stdout
				write(1, " ", 1); //adds space between characters
			}
			printf("\n");
		}
		exit(0);
	} else { //parent closes both ends and waits for children
		close(fds[0]);
		close(fds[1]); 
		wait(0);
	}
	return 0;
}