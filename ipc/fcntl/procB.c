#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main(){
	int fd = open("1.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(fd <0){
		printf("B create 1.txt fail\n");
		return;
	}
	write(fd, "B", 1);
	close(fd);
	return;
}
