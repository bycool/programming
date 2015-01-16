#include <stdio.h>
#include <pthread.h>

pthread_t tid1,tid2;

void* tid1_func(void *arg){
	int a = 10;
	printf("1.tid1.a = %d\n",a);
	sleep(3);
	printf("2.tid1.a = %d\n",a);
}

void* tid2_func(void *arg){
	printf("1.tid2.a = %d\n",a);
}

int main(){
	int err;
	err = pthread_create(&tid1,NULL,tid1_func,NULL); if(err != 0 ) printf("tid1 create err \n");
	err = pthread_create(&tid2,NULL,tid2_func,NULL); if(err != 0 ) printf("tid2 create err \n");
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}

