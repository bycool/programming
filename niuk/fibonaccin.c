#include <stdio.h>

int fibonaccin(int ni){
	int p = 0, n = 1;
	while(ni--){
		n += p;
		p = n - p;
	}
	return p;
}

int main(){
	int n = 10;
	printf("n:%d: %d\n", n, fibonaccin(n));
}
