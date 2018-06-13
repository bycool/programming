#include <stdio.h>
#include <stdlib.h>

void* thread1(){
	mtrace();
	int* pa = (int*)malloc(sizeof(int)*10);
	printf("sizeof: %d",sizeof(pa));
//	free(pa);
}

int main(){
	mtrace();
	pthread_t t1;
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_join(t1);
	void* a = (void*)malloc(10);
	malloc(10);
	free(a);
	return 0;
}
