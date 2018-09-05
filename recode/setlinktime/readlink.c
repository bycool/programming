#include <stdio.h>

int main(){
	int len = 0;
	char path[128];
	len = readlink("1.txt.link", path, 128);
	path[len] = 0;
	printf("srcfile:%s\n", path);
}
