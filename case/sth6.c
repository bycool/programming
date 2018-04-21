#include <stdio.h>

void print(int a){
	printf("%d\n",a);
}

void print(float a){
	printf("%f\n",a);
}

int main(){
	int a = 1;
	int b = 2.1;
	print(a);
	print(b);
}
