#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	struct stat fdst;
	int rc = stat("\\", &fdst);
	if(rc == 0)
		printf("1\n");
	else
		perror("1");

	printf("inode: %lu\n",fdst.st_ino);
	printf("size: %lu\n", fdst.st_size);
}
