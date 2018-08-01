#include <stdio.h>
#include <pthread.h>
#include <mcheck.h>
#include <stdlib.h>

void* tmem(){
	mtrace();
	int i = 5;
	while(i--){
		char* m = (char*)malloc(10);
	}
}

int main(){
	pthread_t t1;
	pthread_create(&t1, NULL, tmem, NULL);
	pthread_join(t1, NULL);
}
