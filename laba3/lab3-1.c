#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	printf("The child process has started.\n");
	pid_t pid = getpid();
	pid_t ppid = getppid();

	printf("PID of the parent process (in child process): %d\n", ppid);
	printf("PID of the child process (in child process): %d\n", pid);

	printf("The envp in child process:\n");
	for(int i = 0; i < 10; i++)
		printf("%s\n", *(envp + i));

	for(int i = 1; i < argc; i++) {
		printf("%s, ", argv[i]);
		fflush(stdout);
		sleep(1);
	}
	putchar('\n');

	printf("The child process has ended.\n");
	exit(3);
}
