// Name: Kian Malakooti
// Date: October 5, 2022 
// Title: Lab3 – Pthreads and inter-process Communication – Pipes
// Description: Step 4

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main() {
	int fds[2];
	pipe(fds);
	//Child 1 duplicates downstream stdin
	if(fork() == 0) {
		dup2(fds[0], 0); //downstream data sent -> stdin
		close(fds[1]); //child 1 closes upstream
		execlp("grep", "grep", "root", NULL);
	}
	//Child 2 duplicates upstream stdout
	else if(fork() == 0) {
		dup2(fds[1], 1); //upstream data -> stdout
		close(fds[0]); //child 2 closes downstream
		execlp("cat", "cat", "/etc/passwd", NULL);
	} else { //closes both ends and waits for children
		close(fds[0]); //closes both ends of pipe
		close(fds[1]); 
		wait(0);
	}
	return 0;
}