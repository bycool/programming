#include <stdio.h>

typedef struct stack{
	int* bas;
	int* top;
	int size;
}stack;

int initstack(stack** st){
	(*st)->bas = (int*)malloc(100);
	(*st)->top = (*st)->bas;
	(*st)->size = 0;
}


