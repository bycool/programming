#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int quit = 0;
int fd = -1;

void sig_quit(int sig){
	printf("ctrl+c\n");
	quit = 1;
	close(fd);
}

int main(){
//	signal(SIGINT, sig_quit);
	char buf[32] = { 0 };
	fd = open("./1.txt", O_CREAT | O_WRONLY | O_APPEND, 0600);
	while(!quit){
		scanf("%s", buf);
		write(fd, buf, strlen(buf));
	}
}

