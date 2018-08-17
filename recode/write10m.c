#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUF_LEN 1024*1024*10

int main(){
	int i = 0;
	int fd = -1;
	char* buf = NULL;
	char* ptr = NULL;

	buf = (char*)malloc(BUF_LEN);
	if(!buf){ printf("buf malloc fail\n"); return 1; }
	ptr = buf;

	
	while(i<BUF_LEN)
		buf[i++] = '1';
//	buf[BUF_LEN] = '\0';

	printf("buf.len: %lu, 10m: %lu\n", strlen(buf), BUF_LEN);
	

	fd = open("10m.txt", O_CREAT | O_WRONLY, 0600);
	write(fd, buf, strlen(buf));
	close(fd);
}
