#include <stdio.h>
#include <pthread.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/time.h> 
#include <sys/socket.h> 
#include <sys/un.h> 
#include <netinet/in.h> 
#include <features.h> 
#include <linux/if.h> 
#include <netpacket/packet.h> 
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <sys/select.h>
#include <stdlib.h>




#include "file_trans.h"

#define MAX_BUF_LEN		1500

static char file_path[FILE_PATH_LEN + 1];
static unsigned short port;
static int sockfd;

typedef struct
{
	struct sockaddr_in client_sock;
	char filename[FILE_NAME_LEN + 1];
}file_trans_param_t;

static void help()
{
	printf("file_server <port> <file_path>\r\n");
}



static void send_file_status(struct sockaddr_in *client_sock, int status)
{
	char buf[1024];
	file_get_rep_msg_t *msg;
	int len;

	MSG_MAGIC_ADD(buf);

	buf[MSG_OFFSET] = FILE_GET_REP;
	msg = (file_get_rep_msg_t *)&buf[MSG_OFFSET + 1];
	msg->file_status = status;
	len = MSG_OFFSET + 1 + sizeof(file_get_rep_msg_t);

	sendto(sockfd, buf, len, 0, (struct sockaddr *)client_sock, sizeof(struct sockaddr_in));
}

static void file_trans(void *arg)
{
	FILE *fp;
	char filepath[FILE_NAME_LEN+FILE_PATH_LEN + 1];
	unsigned char buf[MAX_BUF_LEN];
	file_data_msg_t *msg;
	unsigned char *file_data;
	file_trans_param_t *p;
	int len;

	p= (file_trans_param_t *)arg;
	msg = (file_data_msg_t *)&buf[MSG_OFFSET + 1];
	file_data = &buf[MSG_OFFSET + 1 + sizeof(file_data_msg_t)];

	memset(filepath, 0, sizeof(filepath));
	strcpy(filepath, file_path);
	strcat(filepath, p->filename);

	fp = fopen(filepath, "r");
	if(fp == NULL)
	{
		send_file_status(&p->client_sock, FILE_NOT_FOUND);
		free(p);
		return;
	}
	else
	{
		send_file_status(&p->client_sock, FILE_OK);
	}

	msg->seq = 0;
	msg->status = FILE_TRANS_OK;
	buf[MSG_OFFSET] = FILE_DATA;
	MSG_MAGIC_ADD(buf);

	while((msg->len = fread(file_data, 1, FILE_TRANS_DATA_MAX_LEN, fp)) > 0)
	{
		msg->seq++;
		len = MSG_OFFSET + 1 + sizeof(file_data_msg_t) + msg->len;
		sendto(sockfd, buf, len, 0, (struct sockaddr *)&p->client_sock, sizeof(struct sockaddr_in));
		if(msg->len < FILE_TRANS_DATA_MAX_LEN)
		{
			if(feof(fp))
			{
				break;
			}
			else
			{
				msg->status = FILE_TRANS_ERROR;
				len =  MSG_OFFSET + 1 + sizeof(file_data_msg_t);
				printf("len = %d\r\n", len);
				sendto(sockfd, buf, len, 0, (struct sockaddr *)&p->client_sock, sizeof(struct sockaddr_in));
				goto DONE;
			}
		}
	}

	msg->status = FILE_TRANS_OVER;
	len =  MSG_OFFSET + 1 + sizeof(file_data_msg_t);
	sendto(sockfd, buf, len, 0, (struct sockaddr *)&p->client_sock, sizeof(struct sockaddr_in));

DONE:
	free(p);
	fclose(fp);
}


static void socket_rev()
{
	unsigned char buf[MAX_BUF_LEN];
	file_trans_param_t *p;
	int len;
	socklen_t sock_len = sizeof(struct sockaddr_in);

	p = (file_trans_param_t *)malloc(sizeof(file_trans_param_t));
	if(p == NULL)
	{
		printf("Could not alloc file trans param\r\n");
		return;
	}
	memset(p, 0, sizeof(file_trans_param_t));

	len = recvfrom(sockfd, buf, MAX_BUF_LEN, 0, (struct sockaddr *)&p->client_sock, &sock_len);
	if(len < 5)
	{
		free(p);
		printf("Recv data error\r\n");
		return;
	}

	if(!IS_MY_MSG(buf))
	{
		DBUG();
		free(p);
		return;
	}
	
	if(buf[MSG_OFFSET] == FILE_GET_REQ)
	{
		
		pthread_t pt;
			
		file_get_req_msg_t *msg = (file_get_req_msg_t *)&buf[MSG_OFFSET + 1];
		if(len < (MSG_OFFSET + 1 + sizeof(file_get_req_msg_t)))
		{
			DBUG();
			send_file_status(&p->client_sock, INVALID_FILE_NAME);
			free(p);
			return;
		}

		if(msg->file_name_len > FILE_NAME_LEN)
		{
			DBUG();
			send_file_status(&p->client_sock, FILE_NAME_TOO_LONG);
			free(p);
			return;
		}

		if(len < (MSG_OFFSET + 1 + sizeof(file_get_req_msg_t) + msg->file_name_len))
		{
			DBUG();
			send_file_status(&p->client_sock, INVALID_FILE_NAME);
			free(p);
			return;
			
		}

		memcpy(p->filename, &buf[MSG_OFFSET + 1 + sizeof(file_get_req_msg_t)], msg->file_name_len);
		if(pthread_create(&pt, NULL, (void *)file_trans, (void *)p))
		{
			DBUG();
			printf("Could not create thread\r\n");
			free(p);
			return;
		}

		
	}
	else
	{
		DBUG();
		send_file_status(&p->client_sock, INVALID_FILE_NAME);
		free(p);
		return;
	}
}


static void start_socket()
{
	struct sockaddr_in serv_sock;
	struct sockaddr_in *client_sock;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		printf("Could not create socket\r\n");
		return;
	}

	memset(&serv_sock, 0, sizeof(struct sockaddr_in));
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_sock.sin_port = htons(port);
	if(bind(sockfd, (struct sockaddr *)&serv_sock, sizeof(serv_sock)) < 0)
	{
		printf("Could not bind sock addr\r\n");
		close(sockfd);
		return;
	}

	while(1)
	{
		socket_rev();
	}
	
}



int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Invalid argemnet\r\n");
		help();
		return 0;
	}

	port = atoi(argv[1]);
	memset(file_path, 0, sizeof(file_path));
	memcpy(file_path, argv[2], strlen(argv[2]));

	start_socket();


	return 0;

	
}

