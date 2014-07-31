#ifndef _FILE_TRANS_H_
#define _FILE_TRANS_H_


#define FILE_GET_REQ	0x1
#define FILE_GET_REP	0x2
#define FILE_DATA		0x3


#define PDU_MAX_LEN		1500


#define FILE_NAME_LEN	64
#define FILE_PATH_LEN	128

#define FILE_SER_PORT	9999

#define MSG_MAGIC		"!@#$"

#define MSG_OFFSET	4

#define FILE_NOT_FOUND		0x1
#define FILE_NAME_TOO_LONG	0x2
#define FILE_OK				0x3
#define INVALID_FILE_NAME	0x4

#define FILE_TRANS_DATA_MAX_LEN	1024
#define FILE_TRANS_OK		0x1
#define FILE_TRANS_ERROR	0
#define FILE_TRANS_OVER		0x2


typedef struct
{
	int file_name_len;
}file_get_req_msg_t;

typedef struct
{
	int file_status;
}file_get_rep_msg_t;

typedef struct
{
	int status;
	int len;
	int seq;
}file_data_msg_t;



#define IS_MY_MSG(x)	((x[0] == '!' && x[1] == '@' && x[2] == '#' && x[3] == '$')?1:0)
#define MSG_MAGIC_ADD(buf)	do{ memcpy(buf, MSG_MAGIC, strlen(MSG_MAGIC)); } while(0)


#define DBUG()	printf("%s, %s, %d\r\n", __FILE__, __FUNCTION__, __LINE__);


#endif
