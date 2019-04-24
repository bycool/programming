#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

int exit_flag = 0;

void thread_exit(){
	exit_flag = 1;
}

void* sendthread(int sfd){
	char times[32] = { 0 };
	int rc = 0;
	struct timeval tv;
	while(!exit_flag){
		gettimeofday(&tv, NULL);
		rc = sprintf(times, "%d", tv.tv_usec);
		times[rc] = 0;
		send(sfd, times, strlen(times), 0);
		usleep(100000);
	}
	close(sfd);
}

void main(){
	int cfd;
	int sin_size;
	struct sockaddr_in s_add,c_add;
	int portnum = 8888;
	char ip[32] = "127.0.0.1";

	pthread_t send_thread;

	signal(SIGINT, thread_exit);

	printf("input service.ip:port:");
	scanf("%s %d", ip, &portnum);
	printf("service: %s:%d\n", ip, portnum);

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

	pthread_create(&send_thread, NULL, sendthread, cfd);
	pthread_join(send_thread);
	pthread_exit(NULL);

}
