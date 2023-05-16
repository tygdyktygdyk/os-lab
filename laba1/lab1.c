#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct targs {
	int flag;
	char sym;
};

static void *proc1(void *arg)
{
	printf("The thread 1 has started.\n");
	struct targs *args = (struct targs *)arg;
	while (args->flag == 0) {
		putchar(args->sym);
		fflush(stdout);
		sleep(1);
	}
	printf("\nThe thread 1 has ended.");
	pthread_exit((void *)1);
}

static void *proc2(void *arg)
{
	printf("\nThe thread 2 has started.\n");
	struct targs *args = (struct targs *)arg;
	while (args->flag == 0) {
		putchar(args->sym);
		fflush(stdout);
		sleep(1);
	}
	printf("\nThe thread 2 has ended.");
	pthread_exit((void *)2);
}


int main()
{
	printf("The program has started.\n");

	pthread_t tid1, tid2;

	struct targs arg1, arg2; 
	arg1.flag = 0, arg1.sym = '1';
	arg2.flag = 0, arg2.sym = '2';

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	unsigned long default_stacksize;
	pthread_attr_getstacksize(&attr, &default_stacksize);

	printf("Default stack size: %lu bytes\n", default_stacksize);

	printf("Set new stack size for threads.\n"); 

	pthread_attr_setstacksize(&attr, default_stacksize*2);

	unsigned long new_stacksize;
	pthread_attr_getstacksize(&attr, &new_stacksize);

	printf("New stack size: %lu bytes\n", new_stacksize);

	pthread_create(&tid1, &attr, proc1, &arg1);
	pthread_create(&tid2, &attr, proc2, &arg2);

	printf("\nThe program is waiting for passing ENTER.");

	getchar();

	printf("The key is pressed.");

	arg1.flag = 1, arg2.flag = 1;

	int *exitcode1 = NULL, *exitcode2 = NULL;

	pthread_join(tid1, (void**)&exitcode1);
	pthread_join(tid2, (void**)&exitcode2);

	printf("\nexitcode1 = %p\n", exitcode1);
	printf("exitcode2 = %p\n", exitcode2);

	pthread_attr_destroy(&attr);

	printf("The program has ended.\n");
	return 0;
}
