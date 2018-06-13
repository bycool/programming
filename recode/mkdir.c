#include <stdio.h>
#include <errno.h>

int main(){
	char path[64] = {"./test/hello/v/1"};
	if(mkdir(path) <0)
		perror(path);
}
