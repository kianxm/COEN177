// Name: Kian Malakooti
// Date: October 5, 2022 
// Title: Lab3 – Pthreads and inter-process Communication – Pipes
// Description: Step 5

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char *argv[]) {
	int fds[2];
	char buff[60];
	int count;
	int i;
	memset(buff, 0, sizeof(buff));
	pipe(fds); //initialize pipe
	printf("Input a sentence to send to consumer: \n");
	fgets(buff, sizeof(buff), stdin); //read input into buff
	if(fork() == 0) { //initialize producer
		printf("Producer on upstream end of pipe. \n");
		close(fds[0]); //closes downstream
		write(fds[1], buff, 60); //send buffer data to upstream
		exit(0);
	}
	//initialize consumer
	else if(fork() == 0) {
		printf("\nConsumer on downstream end of pipe \n");
		close(fds[1]); //closes upstream end of pipe
		while((count = read(fds[0], buff, 60)) > 0) { //reads from downstream end of pipe into buffer(buff)
			for(i = 0; i < count; i++)
				write(1, buff+i, 1); //writes buffer to stdout
			printf("\n");
		}
		exit(0);
	}
	else { //parent closes both ends and waits for children
		close(fds[0]);
		close(fds[1]); 
		wait(0);
	}
	return 0;
}