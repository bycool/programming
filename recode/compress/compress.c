#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct userinfo {
	unsigned int userid; //4
	unsigned int age; //4
	unsigned short name_len; //2
	char* name; 
} user;

int buflenofuser(user u1){
	int len = 0;
	len = 4 + 4 + 2 + u1.name_len;
	return len;
}

#define PUT4(UINT, BUF) \
	(BUF)[0] = UINT >> 24,	\
	(BUF)[1] = UINT >> 16,	\
	(BUF)[2] = UINT >> 8,	\
	(BUF)[3] = UINT
	
#define PUT2(UINT, BUF)	\
	(BUF)[0] = UINT >> 8,	\
	(BUF)[1] = UINT

#define PUT4M(UINT, BUF) (PUT4(UINT, BUF), BUF+4)
#define PUT2M(UINT, BUF) (PUT2(UINT, BUF), BUF+2)

int main(){
	user u1;
	u1.userid = 1;
	u1.age = 18;
	char name[32] = {"jiajiandong"};
	u1.name = name;
	u1.name_len = strlen(name)+1;
	printf("uid = %u\n", u1.userid);
	printf("age = %u\n", u1.age);
	printf("namelen = %d\n", u1.name_len);
	printf("name: %s\n",u1.name);

	int u1_len = buflenofuser(u1);
	printf("u1.len: %d\n", u1_len);

	char* u1buf = (char*)malloc(u1_len);
	if(!u1buf){
		printf("malloc fail\n");
		return -1;
	}
	char* p = u1buf;
	PUT4M(u1.userid, p);
	PUT4M(u1.age, p);
	PUT2M(u1.name_len, p);
	memcpy(p, u1.name, u1.name_len);

	printf("u1.id: %d\n",(unsigned int)u1buf);

#if 0
	printf("u int  :%d\n", sizeof(unsigned int));
	printf("u short:%d\n", sizeof(unsigned short));
	printf("char*  :%d\n", sizeof(char*));
	printf("sizeof user : %d\n", sizeof(user));
#endif

	

}

