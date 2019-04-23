#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>

void main(){
	int sfd, cfd;
	int portnum = 8888;
	int sin_size;
	char buffer[32]={0};
	struct sockaddr_in s_add,c_add;
	struct timeval tv;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1){ printf("socket fail\n") ; return; } printf("socket ok\n");

	bzero(&s_add, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = htonl(INADDR_ANY);
	s_add.sin_port=htons(portnum);

	if(-1 == bind(sfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr))){
		printf("bind fail !\n");
		return ;
	}
	printf("bind ok !\n");

	if(-1 == listen(sfd, 10)){
		printf("listen fail !\n");
		return ;
	}
	printf("listen ok\n");

	while(1){
		sin_size = sizeof(struct sockaddr_in);
		cfd = accept(sfd, (struct sockaddr *)(&c_add), &sin_size);

		if(read(cfd, buffer, 32) == -1) return ;
		gettimeofday(&tv, NULL);
		printf("%d:%s\n", tv.tv_usec, buffer);

		close(cfd);
	}

	close(sfd);
}

