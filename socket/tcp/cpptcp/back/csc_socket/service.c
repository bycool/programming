#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>

int fds[10]={0};

void* handle(void* argc){
	int newsock = (int)argc;
	char buf[1024];
	int k=0;
	while(1){
		int s = read(newsock, buf,sizeof(buf));
		if(s > 0){
			buf[s] = 0;
			printf("client[%d]:%s\n",newsock,buf);
			for(k=0;k<10;k++){
				printf("fds[%d]:%d\n",k,fds[k]);
				if(fds[k]!=0){
					write(fds[k],buf,strlen(buf));
				}
			}
		}else if(s==0){
			printf("client[%d] quite\n",newsock);
			break;
		}
	}
	close(newsock);
}

int main(){
	int sfp,nfp;
	char buffer[1024]={0};
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
	if(-1 == listen(sfp,1)){
	    printf("listen fail !\n");
	    return -1;  
	}
	printf("listen ok\n");
    int cnt = 0;
	while(1){
		sin_size = sizeof(struct sockaddr_in);  
		nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);

		if(-1 == nfp){
		    printf("accept fail !\n");
		    return -1;
		}
		fds[cnt++]=nfp;
		printf("accept ok!\nServer start get connect from client[%d]:%#x : %#x\n",nfp,ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));

		pthread_t tid;
		pthread_create(&tid,NULL,handle,(void*)nfp);
		pthread_detach(tid);

	
	}
	close(sfp);
	return 0;
}


