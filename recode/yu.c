#include <stdio.h>

#define SOCK_TYPE_MASKM 0xf

void main(){
	int type = 1;
	int flage = -1;

	flage = type & ~SOCK_TYPE_MASKM;

	printf("flage : %d\n", flage);
}
