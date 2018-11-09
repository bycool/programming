#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(){
	int fd = open("./1.txt", O_CREAT | O_WRONLY, 0600);
	int rc = -1;
	if((rc = write(fd,"1\0",2)) != 2 || rc < 0){
		printf("%d:%s\n", errno, strerror(errno));
		printf("rc: %d\n", rc);
	}
	close(fd);
	return 0;
}
