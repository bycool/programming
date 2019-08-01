#include <stdio.h>

int main(){
	int a = 1, b = 2, c = 3, d = 4;
	int rc = -1;

	rc = a > b ? a : b;
	printf("rc =  %d\n", rc);

	//(a>b?a:b) = 10;  //此处错误，(a>b?a:b) 表达式返回的是2(b的值),而不是b.

	*(a>b?&a:&b) = 10;
	printf("a: %d, b: %d\n", a, b);

}
