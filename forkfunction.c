#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* needed to fork() and get pid()*/
#include <sys/wait.h>
#include <sys/types.h>

void childTask() 
{
	printf("Salam,saya anak tau\n");
}

void parentTask()
{
	printf("Dan saya adalah bapaknya\n");
}

int main (void)
{
        pid_t pid = fork();

	if(pid == 0)
	{
		childTask();
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0)
	{
		wait(NULL);
		parentTask();
	}
	else
	{
		printf("Unable to create child process.");
	}
	return EXIT_SUCCESS;
}
