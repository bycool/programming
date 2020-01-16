#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

void main(){
	char buf[10] = {"hellow"};
	int fd = open("12.txt", O_CREAT | O_RDWR, 0600);
	if(fd < 0){
		printf("file open error\n");
		return ;
	}
	
	ftruncate(fd,10);

	char* mpt = mmap(0, 10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
	if(mpt == MAP_FAILED){
		printf("mmap fail\n");
		return ;
	}

	//sprintf(mpt, "hellow");

	munmap(mpt, 10);
	close(fd);
	
}
