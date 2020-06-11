#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>


static inline char *
skip_token(const char *p)
{
    while (isspace(*p)) p++;
    while (*p && !isspace(*p)) p++;
    while (isspace(*p)) p++;
    return (char *)p;
}


int get_proc_mem()
{
    int fd = -1;

    char stat_file[512] = {0};
    char stat_buf[4096] = {0};
    int rbytes = 0;
    char* p = NULL;

    snprintf(stat_file, sizeof stat_file, "/proc/%d/stat", getpid());

    fd = open(stat_file, O_RDONLY);
    if (fd < 0)
    {
		printf("open stat_file[%s] failed\n", stat_file);
        return -1;
    }
    
    rbytes = read(fd, stat_buf, sizeof(stat_buf) - 1);
    close(fd);

	printf("p: %s\n", stat_buf);
    
    if (rbytes <= 0)
    {
        return -1;
    }

    p = stat_buf;
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);
    p = skip_token(p);

	printf("p: %s\n", p);
    return strtoul(p, &p, 10) * 4 / 1024;
}


void main(){
	char *c = (char*)malloc(1024*1028*1024);
	if(c==NULL){
		printf("malloc fail\n");
		return;
	}
	memset(c, 0x0, 1024*1024*1024);
	printf("mem: %d\n", get_proc_mem());
	getchar();


	free(c);
}
