#include <stdio.h>

struct fds_foperate_info
{
    int name_len;           /* 文件完整路径长度 */
    int op_type;            /* 操作类型编号 */
    int file_inode;         /* 操作码文件inode */
    void* args;               /* 其他参数 */
};


int main(){
	char name[1024];
	printf("long long: %d\n",sizeof(long long));
	printf("long     : %d\n",sizeof(unsigned long));
	printf("%d\n",sizeof(name));
	printf("%d\n",sizeof(void*));

	printf("struct:%d\n",sizeof(struct fds_foperate_info));
}
