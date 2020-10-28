#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
int val = 0;


void* printval(void* who){
	while(val<10){
		pthread_mutex_lock(&mlock);
		printf("%d:  [%d]\n", *(int*)who, val++);
		pthread_mutex_unlock(&mlock);
		sleep(val%5+1);
	}
}

void main(){
	int i1 =1, i2 =2;
	pthread_t t1,t2;
	if( pthread_create(&t1, NULL, printval, (void*)&i1) == -1){
		printf("create pthread  1 failed\n");
	}
	if( pthread_create(&t2, NULL, printval, (void*)&i2) == -1){
		printf("create pthread  2 failed\n");
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
//	pthread_detach(t1);
//	pthread_detach(t2);

	pthread_exit(NULL);
}
