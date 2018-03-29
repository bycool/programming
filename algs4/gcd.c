#include <stdio.h>

int gcd(int a,int b){
	if(b==0) return a;
	int r = a%b;
	printf("%d\t%d\n",b,r);
	return gcd(b,r);
}

int main(){
	int a = gcd(12,15);
	printf("%d\n",a);
}
