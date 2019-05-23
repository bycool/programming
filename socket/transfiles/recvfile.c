#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

/*  recvfile.c
 *  接受客户端文件
 */

static int s_sock;
static int port;


int socket_init(){
	int c_sock;
	struct sockaddr_in s_addr,c_addr;

	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(s_socket == -1) { printf("service socket create fail\n"); return -1; }

	bzero(&s_addr, sizeof(sockaddr_in));
	s_addr.sin_fimaly = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(port);

	if(bind(s_sock, (struct sockaddr*)(&s_addr), sizeof(struct sockaddr)) == -1){
		printf("service socket bind fail\n"); return -1;
	}
	
	if(listen(s_sock, 10) == -1){
		printf("service socket listen fail\n"); return -1;
	}

	
}




void main(int argc, char* argv[]){
	int ch;

	while((ch = getopt(argc, argv, "p:")) != -1){
		switch(ch){
			case 'p':
				port = atoi(optarg);
				break;
			default:
				port = 8888;
				printf("default port: 8888\n");
				break;
		}
	}

	

	
}
