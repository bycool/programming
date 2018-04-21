#include <stdio.h>
#include <stdlib.h>

int main(){
	unsigned long a = 25;
	printf("%o\n",a); //8bit
	printf("%x\n",a); //16bit
	int b = 1;
	printf("%d\n",sizeof a);
	printf("%d\n",sizeof b);
}
