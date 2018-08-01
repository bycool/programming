#include <stdio.h>
#include <pthread.h>

void* threadp_t1(){
	int i = 1;
	while(i<100){
		printf("t1: %d\n",i);
		i+=2;
		sleep(1);
	}
}

void* threadp_t2(){
	int i = 0;
	while(i<100){
		printf("t2: %d\n",i);
		i+=2;
		sleep(1);
	}
}


int main(){
	pthread_t t1, t2;
	pthread_create(&t1, NULL, threadp_t1, NULL);
	pthread_detach(t1);
	pthread_create(&t2, NULL, threadp_t2, NULL);
	pthread_detach(t2);
	pthread_exit(NULL);
}
