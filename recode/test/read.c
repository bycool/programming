#include <stdio.h>
#include <fcntl.h>

char *pathname = "/mnt/debugfs/.dchan00";

unsigned long FDS_Build_Bytes_TO_Figure(unsigned char *str, int byte)
{
    int i;
    unsigned long result = 0;
    if(str == NULL || byte < 1)
    {
        return -1;
    }

    for(i = 0; i < byte; i ++)
    {
        result += ((unsigned long)str[i]) << (8 * (byte - 1 - i));
    }
    return result;
}


int main(){
	int fd = open(pathname,O_RDONLY);
	unsigned char buf[32];
	int ret = read(fd,buf,4);
	unsigned long num = FDS_Build_Bytes_TO_Figure(buf,4);
	printf("%u\n",num);
}
