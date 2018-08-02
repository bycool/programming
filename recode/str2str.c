#include <stdio.h>
#include <string.h>

int main(){
	char a[4] = {"123"};
	char b[4] = {0};
	strcpy(b,a);
	printf("b:%s\n",b);
}
