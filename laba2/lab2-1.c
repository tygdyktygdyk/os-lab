#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int flag1 = 0, flag2 = 0;

sem_t semid;

static void *proc1(void *)
{
	printf("The thread 1 has started.\n");
	while(flag1 != 1) {
		sem_wait(&semid);
		for(int i=0; i<10; i++) {
			putchar('1');
			fflush(stdout);
			sleep(1);
		}
		sem_post(&semid);
		sleep(1);
	}
	printf("\nThe thread 1 has ended.\n");
	pthread_exit(NULL);
}

static void *proc2(void *)
{
	printf("The thread 2 has started.\n");
	while(flag2 != 1) {
		sem_wait(&semid);
		for(int i=0; i<10; i++) {
			putchar('2');
			fflush(stdout);
			sleep(1);
		}
		sem_post(&semid);
		sleep(1);
	}
	printf("\nThe thread 2 has ended.\n");
	pthread_exit((void *)2);
}

int main()
{
	printf("The program has started.\n");

	pthread_t tid1, tid2;

	sem_init(&semid, 0, 1);

	pthread_create(&tid1, NULL, proc1, NULL);
	pthread_create(&tid2, NULL, proc2, NULL);

	printf("\nThe program is waiting for passing ENTER.\n");

	getchar();
	
	printf("The key is pressed.\n");

	flag1 = 1; flag2 = 1;

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	sem_destroy(&semid);

	printf("The program has ended.\n");
	return 0;
}
