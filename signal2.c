#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

void sigint_handler(int sig);
void sigtstp_handler(int sig);
void sigquit_handler(int sig);

int main(void)
{
	char s[200];

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}

        if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR)
        {
                perror("signal");
                exit(1);
        }

	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
        {
                perror("signal");
                exit(1);
        }


	printf("Enter a string:\n");

	if (fgets(s, 200, stdin) == NULL)
		perror("gets");
	else
		printf("You entered: %s\n", s);

	return (0);
}

void sigint_handler(int sig)
{
	printf("This is a special signal handler for CTRL + C, sig = %d\n", sig);
}

void sigquit_handler(int sig)
{
        printf("This is a special signal handler for CTRL + \\, sig = %d\n", sig);
}
void sigtstp_handler(int sig)
{
        printf("This is a special signal handler for CTRL + Z, sig = %d\n", sig);
}
