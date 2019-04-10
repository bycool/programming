#include <stdio.h>

int gcd(int a, int b){
	if(b==0) return a;
	int r = a%b;
	return gcd(b, r);
}

void main(){
	int a = gcd(15,12);

	printf("a:%d\n",a);
}
