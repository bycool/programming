#include <stdio.h>
#include <stdlib.h>

void initint(int** a){
	*a = (int*)malloc(4);
	int *tmp = *a;
	*tmp  = 2;
}

int main(){
	int *t = NULL;
	initint(&t);
//	*t = 1;
	printf("%d\n",*t);
	free(t);
}
