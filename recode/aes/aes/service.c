#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>
#include "aes128.h"

void* handle(void* argc){
	int newsock = (int)argc;
	uint8_t* deout = 0;
	char buf[2048];
	while(1){
		int s = read(newsock, buf,sizeof(buf));
		printf("buf.size: %d\n", s);
		aes128_de(buf, s);
		if(s > 0){
			buf[s] = 0;
			printf("pid: %d -- client[%d]:%s\n",pthread_self(),newsock, buf);
			write(newsock,buf,strlen(buf));
			free(deout);
		}else if(s==0){
			printf("client quite\n");
			break;
		}
	}
	close(newsock);
}

int main(){
	int sfp,nfp;
	char buffer[2048]={0};
	struct sockaddr_in s_add,c_add;
	int sin_size;
	int portnum=8889;

	printf("Hello,welcome to my server !\n");
	sfp = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfp){
	    printf("socket fail !\n");
	    return -1;
	}
	printf("socket ok !\n");

	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr=htonl(INADDR_ANY);
	s_add.sin_port=htons(portnum);
	if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr))){
	    printf("bind fail !\n");
	    return -1;
	}
	printf("bind ok !\n");
	if(-1 == listen(sfp,10)){
	    printf("listen fail !\n");
	    return -1;  
	}
	printf("listen ok\n");
    
	while(1){
		sin_size = sizeof(struct sockaddr_in);  
		nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);

		if(-1 == nfp){
		    printf("accept fail !\n");
		    return -1;
		}
		printf("accept ok!\nServer start get connect from client[%d]:%#x : %#x\n",nfp,ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));

		pthread_t tid1,tid2,tid3;
		pthread_create(&tid1,NULL,handle,(void*)nfp);
		pthread_create(&tid2,NULL,handle,(void*)nfp);
		pthread_create(&tid3,NULL,handle,(void*)nfp);
		pthread_detach(tid1);
		pthread_detach(tid2);
		pthread_detach(tid3);

	
	}
	close(sfp);
	return 0;
}


