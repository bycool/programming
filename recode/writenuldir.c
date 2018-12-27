#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(){
	int fd = open("2/1.txt", O_CREAT | O_WRONLY , 0600);
	if(fd < 0){
		printf("[%d|%s|\n", errno, strerror(errno));
	}
	return 0;
}
