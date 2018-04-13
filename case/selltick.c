#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int tick = 20;
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

void* seller(void* no){
	pthread_mutex_lock(&mlock);
	while(1){
		if(tick>0){
			tick--;
			printf("tick:%d, seller:%d\n",tick,(int*)no);
			pthread_mutex_unlock(&mlock);
			sleep(1);
		}else{
			pthread_mutex_unlock(&mlock);
			break;
		}
	}
}

int main(){
	pthread_t t1,t2;
	pthread_mutex_init(&mlock,NULL);

	pthread_create(&t1,NULL,seller,(void*)1);
	pthread_create(&t2,NULL,seller,(void*)2);
	pthread_detach(t1);
	pthread_detach(t2);

	pthread_exit(NULL);
}

