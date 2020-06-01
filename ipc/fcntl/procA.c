#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main(){
	int fd = open("1.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(fd <0){
		printf("A create 1.txt fail\n");
		return;
	}
	write(fd, "A", 1);
	sleep(10);
	close(fd);
	return;
}
