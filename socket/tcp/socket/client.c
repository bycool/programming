#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>
#include <sys/time.h>

void main(){
	int cfd;
	int sin_size;
	char buffer[1024] = { 0 };
	struct sockaddr_in s_add,c_add;
	int portnum = 8888;
	char ip[] = "127.0.0.1";
	struct timeval tv;
	char times[32] = { 0 };
	int rc = 0;

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd == -1) { printf("socket fail\n"); return ;} printf("socket ok\n");

	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr(ip);
	s_add.sin_port=htons(portnum);

	if( connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)) == -1){
		printf("connect fail !\n");
		return ;
	}
	printf("connect ok !\n");

	while(1){
		gettimeofday(&tv, NULL);
		rc = sprintf(times, "%d", tv.tv_usec);
		times[rc] = 0;
		write(cfd, times, strlen(times)+1);
	}
	close(cfd);
}
