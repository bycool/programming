#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

int gi = 21;

int exit_flag = 0;

void exitflag(){
	printf("ctrl+c\n");
	exit_flag = 1;
}

void* print(void* args){
	int i = *(int*)args;
	while(!exit_flag){
		pthread_mutex_lock(&mlock);
		gi--;
		printf("user: %d, gi: %d \n", i, gi);
		pthread_mutex_unlock(&mlock);
		sleep(i);
	}
	printf("exit: %d\n", i);
}

void main(){
	pthread_t t1, t2, t3;
	signal(SIGINT, exitflag);
	int i1 = 1, i2 = 2, i3 = 3;
	pthread_create(&t1, NULL, print, &i1);
	pthread_create(&t2, NULL, print, &i2);
	pthread_create(&t3, NULL, print, &i3);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	printf("exit main\n");
	pthread_exit(NULL);
}

