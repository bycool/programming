#include <stdio.h>


//c: 12:  0 0 0 0 0 0 0 0
//                8 4 2 1

struct node {
	unsigned long i;
	int b;
	long c;
	char e;
};


void main(){
	struct node n = {4, 4, 4, '4'};
	printf("sizeof(node): %d\n", sizeof(n));
	printf("i:%p\n", &(n.i));
	printf("b:%p\n", &(n.b));
	printf("c:%p\n", &(n.c));
	printf("e:%p\n", &(n.e));
}

