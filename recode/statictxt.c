#include <stdio.h>
#include <stdlib.h>

static char* p = NULL;

void main(){
	p = (char*)malloc(10);
	printf("%p\n", p);
	p = (char*)malloc(10);
	printf("%p\n", p);
	p = (char*)malloc(10);
	printf("%p\n", p);
}
