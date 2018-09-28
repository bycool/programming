#include <stdio.h>
#include <stdlib.h>

int main(){
	char* tmp = (char*)malloc(10);
	printf("sizeof tmp : %d\n", sizeof tmp);

	free(tmp);
}
