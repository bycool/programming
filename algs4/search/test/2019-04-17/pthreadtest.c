#include <stdio.h>
#include <pthread.h>
#include <

void* pthread_print(void* args){
	int i = *(int*)args;
	int cnt = 10;
	while(cnt--){
		printf("thread:%d, cnt:%d\n", i, cnt);
		usleep(1000000);
	}
}

void main(){
	int i = 1, k = 2, l = 3;
	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, pthread_print, &i );
	pthread_create(&t2, NULL, pthread_print, &k );
	pthread_create(&t3, NULL, pthread_print, &l );
	pthread_detach(t1);
	pthread_detach(t2);
	pthread_detach(t3);
	pthread_exit(NULL);
}
