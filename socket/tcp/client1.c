#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>


//int cfd; /* 文件描述符 */
int recbytes;
int sin_size;
char buffer[1024]={0};    /* 接受缓冲区 */
unsigned short portnum=0x8888;  /* 服务端使用的通信端口，可以更改，需和服务端相同 */
char* ip = "192.168.6.202";


int csocket(){
	/* 建立socket 使用因特网，TCP流传输 */
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
	struct sockaddr_in s_add,c_add; /* 存储服务端和本端的ip、端口等信息结构体 */
	/* 构造服务器端的ip和端口信息，具体结构体可以查资料 */
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	//s_add.sin_addr.s_addr= inet_addr("192.168.6.202"); /* ip转换为4字节整形，使用时需要根据服务端ip进行更改 */
	printf("%s\n",ip);
	s_add.sin_addr.s_addr= inet_addr(ip); /* ip转换为4字节整形，使用时需要根据服务端ip进行更改 */
	s_add.sin_port=htons(portnum); 

	/* 客户端连接服务器，参数依次为socket文件描述符，地址信息，地址结构大小 */
	if(-1 == connect(cfds,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
	    printf("connect fail !\r\n");
	    return -1;  
	}
	printf("connect ok !\r\n");
}

int main(){

	printf("Hello,welcome to client !\r\n");
	int myfd = csocket();
	cconnect(myfd, ip, portnum);

	if( -1 == write(myfd,"ctos\n",6)) return -1;

	char buf[6];
	recv(myfd, buf, sizeof(buf), 0);
	printf("recv:%s\r\n",buf);

	getchar(); /* 此句为使程序暂停在此处，可以使用netstat查看当前的连接 */
	close(myfd); /* 关闭连接，本次通信完成 */
	return 0;



}
