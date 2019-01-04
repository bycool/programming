#include <stdio.h>

int main(){
	char buf[2] = { 0 };
	buf[0] = 'a';
	buf[1] = 32;
	printf("%c, %c, %d, %d\n", buf[0], buf[1], buf[0], buf[1]);

	int a = buf[1];
	printf("a:%d\n", a);
}
