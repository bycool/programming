
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
 
int main()
{
    int fd1,fd2,fd3,nr;
    char buff[20];
    pid_t pid;
    fd1 = open("1.txt",O_RDWR);
    pid = fork();
    if(pid == 0)
    {   
        nr = read(fd1,buff,10);
        buff[nr]='\0';
        printf("pid#%d content#%s#\n",getpid(),buff);
        exit(0);
    }   
    nr = read(fd1,buff,10);
    buff[nr]='\0';
    printf("pid#%d content#%s#\n",getpid(),buff);
    return 0;
}

