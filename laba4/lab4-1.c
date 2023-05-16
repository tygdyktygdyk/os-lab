#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <string.h>

int keypressed()
{
	fd_set readfds;
    	struct timeval tv;
    	int retval;

    	tv.tv_sec = 0;
    	tv.tv_usec = 0;

    	FD_ZERO(&readfds);
    	FD_SET(0, &readfds);

    	retval = select(1, &readfds, NULL, NULL, &tv);
    	if (retval == -1) {
        	perror("select()");
        	return 0;
    	} else if (retval) {
        	return 1;
    	} else {
        	return 0;
    	}
}

int main()
{
	printf("The lab4-1 has started.\n");
	int flag = 0;
	FILE *fileds = fopen("lab4.txt", "a");
	if(fileds == NULL)
		fileds = fopen("lab4.txt", "w");
	sem_t *semid = sem_open("/main_semaphore", O_CREAT, 0644, 1);
	while(flag != 1) {
		printf("The program is waiting for passing ENTER.\n");
		sem_wait(semid);
		for(int i = 0; i < 5; i++) {
			fputc('1', fileds);
			fflush(fileds);
			putchar('1');
			fflush(stdout);
			sleep(1);
		}
		sem_post(semid);
		sleep(1);
		if(keypressed()) {
			printf("The key is pressed.\n");
			flag = 1;
			break;
		}
	}
	fclose(fileds);
	sem_close(semid);
	sem_unlink("/main_semaphore");
	printf("The lab4-1 has ended.\n");
	return 0;
}
