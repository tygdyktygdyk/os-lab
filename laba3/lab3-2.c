#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	printf("The parent process has started.\n");
	pid_t pid = fork();

	if(pid == 0)
		execle("lab3-1", "lab3-1", "one", "two", "three", "four", "five", "six", NULL, envp);

	else if(pid > 0) {

		printf("The envp in parent process:\n");
		for(int i = 0; i < 10; i++)
			printf("%s\n", *(envp + i));

		printf("PID of the parent process: %d, PID of the child process: %d\n", getpid(), pid);
		int status;
		while(waitpid(pid, &status, WNOHANG) == 0) {
			printf("Waiting.\n");
			sleep(1);
		}
		printf("Child process exit code: %d\n", status);
	}
	else
		perror("fork");

	printf("The parent process has ended.\n");
	return 0;
}
