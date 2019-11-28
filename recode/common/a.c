#include <stdio.h>
#include <unistd.h>
#include "comm.h"

void main(){
	int* a = NULL;
	geta(&a);
	*a = 2;
	printf("*a = %d\n", *a);
	pause();
}
