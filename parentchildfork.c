#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* needed to fork() and get pid()*/
#include <sys/wait.h>
#include <string.h>

int main (int argc, char* argv[])
{
        pid_t pid;

	switch(pid = fork()){
	
	case 0: 
		printf("I am the child process: pid=%d\n", pid);
		break;

	default:
		wait(NULL);
		printf("I am the parent process: pid=%d, child pid=%d\n", getpid(),pid);
		break;

	case -1:
		perror("fork");
		exit(1);

	}
	exit(0);
}
