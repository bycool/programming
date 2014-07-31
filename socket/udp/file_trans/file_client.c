#include <stdio.h>
#include <unistd.h> 
#include <string.h> 
#include <pthread.h> 
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

#define TIME_OUT_SEC	1


int send_file_get_req(int sock, struct sockaddr_in *serv_sock, char *filename)
{
	char buf[128];
	file_get_req_msg_t *msg;
	char *data;
	int len;
	
	MSG_MAGIC_ADD(buf);

	buf[MSG_OFFSET] = FILE_GET_REQ;
	msg = (file_get_req_msg_t *)&buf[MSG_OFFSET + 1];
	data = &buf[MSG_OFFSET + 1 + sizeof(file_get_req_msg_t)];
	msg->file_name_len = strlen(filename);
	memcpy(data, filename, strlen(filename));

	len = MSG_OFFSET + 1 + sizeof(file_get_req_msg_t) + strlen(filename);

	if(sendto(sock, buf, len, 0, (struct sockaddr *)serv_sock, sizeof(struct sockaddr_in)) < len)
	{
		printf("Send msg error\r\n");
		return -1;
	}

	return 0;
	
}


static void file_trans(int sock, struct sockaddr_in *serv_sock, char *filename)
{
	fd_set rfds;    
	struct timeval tv;
	unsigned char buf[1500];
	int len;
	FILE *fp = NULL;
	file_get_rep_msg_t *rep_msg = (file_get_rep_msg_t *)&buf[MSG_OFFSET+1];
	file_data_msg_t *data_msg = (file_data_msg_t *)&buf[MSG_OFFSET+1];
	unsigned char *file_data = &buf[MSG_OFFSET+1+sizeof(file_data_msg_t)];
	int done = 0;
	int seq = 0;
	int total_len = 0;

	int ret;

	
	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);
		tv.tv_sec = TIME_OUT_SEC;        
		tv.tv_usec = 0;
	
		ret = select(sock + 1, &rfds, NULL, NULL, &tv);
		if(ret < 0)
		{
			printf("Select error\r\n");
			goto DONE;
		}
		if(ret == 0)
		{
			printf("Time out\r\n");
			goto DONE;
		}

		if(!FD_ISSET(sock, &rfds))
		{
			continue;
		}

		len = recv(sock, buf, 1500, 0);
		if(len < 5)
		{
			printf("Recv error\r\n");
			continue;
		}

		if(!IS_MY_MSG(buf))
		{
			continue;
		}

		switch(buf[MSG_OFFSET])
		{
			case FILE_GET_REP:
				if(len < (MSG_OFFSET+1+sizeof(file_get_rep_msg_t)))
				{
					printf("Bad msg\r\n");
					goto DONE;
				}
				switch(rep_msg->file_status)
				{
					case FILE_NOT_FOUND:
						printf("File not found\r\n");
						goto DONE;
					case FILE_NAME_TOO_LONG:
						printf("File name too long\r\n");
						goto DONE;
					case INVALID_FILE_NAME:
						printf("Invalid file name\r\n");
						goto DONE;
					default:
						break;
				}
				fp = fopen(filename, "w+");
				if(fp == NULL)
				{
					DBUG();
					printf("Could not create file:%s\r\n", filename);
					goto DONE;
				}
				printf("Create file:%s\r\n", filename);
				break;
			
			case FILE_DATA:
				if(len < (MSG_OFFSET+1+sizeof(file_data_msg_t)))
				{
					printf("Bad msg\r\n");
					goto DONE;
				}
				switch(data_msg->status)
				{
					case FILE_TRANS_OK:
						if(len < (MSG_OFFSET+1+sizeof(file_data_msg_t) + data_msg->len))
						{
							DBUG();
							printf("Invalid msg, len = %d\r\n", len);
							goto DONE;
						}

						if(data_msg->seq != ++seq)
						{
							printf("lost data\r\n");
							goto DONE;
						}
						
						printf("#");
						fwrite(file_data, 1, data_msg->len, fp);
						total_len += data_msg->len;
						fflush(stdout);
						break;
					case FILE_TRANS_ERROR:
						printf("Trans error\r\n");
						goto DONE;
					case FILE_TRANS_OVER:
						done = 1;
						goto DONE;
					default:
						goto DONE;
				}
				break;
			default:
				goto DONE;
		}
	}

DONE:

	if(fp != NULL)
	{
		fclose(fp);
		if(!done)
		{
			remove(filename);
		}
		else
		{
			printf("\r\nDone, total len = %d\r\n", total_len);
		}
	}

	return;
	
}

int main(int argc, char *argv[])
{
	unsigned short serv_port;
	char *ip;
	char *filename;
	int sock;
	struct sockaddr_in serv_sock;
	
	
	if(argc < 4)
	{
		printf("Bad argument\r\n");
		printf("file_client <ip> <port> <filename>\r\n");
		return;
	}


	ip = argv[1];
	serv_port = atoi(argv[2]);
	filename = argv[3];

	if(strlen(filename) > FILE_NAME_LEN)
	{
		printf("File name len is too long\r\n");
		return 0;
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		printf("Could not create socket \r\n");
		return 0;
	}

	memset(&serv_sock, 0, sizeof(struct sockaddr_in));
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_addr.s_addr = inet_addr(ip);
	serv_sock.sin_port = htons(serv_port);

	if(send_file_get_req(sock, &serv_sock, filename) < 0)
	{
		return 0;
	}

	file_trans(sock, &serv_sock, filename);

	close(sock);

	return 0;
	
}
