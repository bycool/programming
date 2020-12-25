#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* printsth(void *data){
	int cnt = 5;
	while(cnt--){
		printf("printsth: %s\n", (char*)data);
		sleep(1);
	}
}

void main(){
	int ret = 0;
	pthread_t prt;
	ret = pthread_create(&prt, NULL, printsth, "hello");
	pthread_join(prt, NULL);
	

}
