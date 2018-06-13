#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
    int fd;
    if((fd=creat("jiangdunchuan.c",S_IRWXU))==-1){
        perror("creat error !\n");
        exit(0);
    }else{
        //int fd=open("jiangdunchuan.c",O_RDWR);
        if(write(fd,"ni hao !",sizeof("ni hao !")-1)==-1){
            perror("write error !\n");
            exit(0);
        }else{
            if(write(fd,"jiangdunchuan !",sizeof("jiangdunchuan !"))==-1){
                perror("error !\n");
                exit(0);
            }
            printf("successful !\n");
        }
		char buff[100];
        //int fd2=open("jiangdunchuan.c",O_RDWR);
        if(read(fd,buff,100)==-1){
            perror("read error !\n");
            exit(0);
        }else{
            printf("%s\n",buff);
            printf("ok\n");
        }
    }
    return 0;
}
