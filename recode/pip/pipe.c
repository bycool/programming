#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#define FIFO "/home/teanee/test/pipe"
main(int argc,char ** argv){
    char buf_r[100];
    int fd;
    int nread;
    if((mkfifo(FIFO,O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))        //O_EXCL:可执行
        printf("cannot create FIFOserver\n");
    printf("Preparing for reading bytes...\n");
    memset(buf_r,0,sizeof(buf_r));
    fd=open(FIFO,O_RDONLY|O_NONBLOCK,0);        //O_RDONLY:只读，O_NONBLOCK:非阻塞
    if(fd==-1){
        perror("open");
        exit(1);
    }
    while(1){
        memset(buf_r,0,sizeof(buf_r));
        if((nread=read(fd,buf_r,100))==-1){
            if(errno==EAGAIN)
                printf("no data yet\n");
        }
        printf("read %s from FIFO\n",buf_r);
        sleep(1);
    }
    pause();
    unlink(FIFO);
} 
