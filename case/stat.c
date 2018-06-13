#include <sys/stat.h>
#include <stdio.h>

int main(){
	struct stat fdst;
	stat("./1.txt",&fdst);
	printf("%d\n",fdst.st_ino);
}
