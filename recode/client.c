#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "aes128.h"


int recbytes;
int sin_size;
char buffer[1024]={0};
int portnum=8889;  
char* ip = "192.168.253.145";
//char* ip = "192.168.0.62";


int csocket(){
	int cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == cfd)
	{
	    printf("socket fail ! \r\n");
	    return -1;
	}
	printf("socket ok !\r\n");
	return cfd;
}

int cconnect(int cfds, char* ip,int portm){
	struct sockaddr_in s_add,c_add;
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	printf("%s\n",ip);
	s_add.sin_addr.s_addr= inet_addr(ip);
	s_add.sin_port=htons(portnum); 

	if(-1 == connect(cfds,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
	    printf("connect fail %d[%s]\n", errno, strerror(errno));
	    return -1;  
	}
	printf("connect ok !\r\n");
}
/*
void client_recv(void* fd){
	char recv_buf[100];
	int service_fd = (int)fd;
	int ret =1;
	memset(recv_buf,0,sizeof(recv_buf));
	while(1){
		printf("client read to recv\n");

		ret = recv(service_fd, &recv_buf, sizeof(recv_buf),0);
		if(ret==0) break;
		printf("service: %s\n",recv_buf);
	}
}
*/
int main(){
	int keepalive = 1;
	int len = 0;
	uint8_t* enout = 0;
	int out_len = 0;
	printf("Hello,welcome to client !\r\n");
	int myfd = csocket();
	cconnect(myfd, ip, portnum);

	char buffer[1024] = "<DATAFILE TargetId=\"%d\" FullId=\"1\" FzsNo=\"1\" Enc=\"1\" SIZE=\"1\" Zip=\"1\" ZipSize=\"1\"/>";
	char buf[256];
	len = strlen(buffer);

	out_len = aes128_en(buffer, len, &enout);

//	printf("buffer.size: %d\n", out_len);

	if( -1 == write(myfd, enout , out_len)) return -1;

	free(enout);
	int s = recv(myfd, buf, sizeof(buf), 0);
	if(s>0){
		buf[s] = 0;
		printf("recv:%s\n",buf);
	}
	close(myfd);
	return 0;



}
