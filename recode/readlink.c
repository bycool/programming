#include <stdio.h>
#include <string.h>

int main(){
	char buf[1024] = {"111111111111111111111111111"};
	printf("%s\n", buf);
	readlink("1.link", buf, 1024);
	printf("%s, %d\n", buf, strlen(buf));
}