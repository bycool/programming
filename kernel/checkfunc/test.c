#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

main()
{
    int fd;

    fd = open("/dev/hello",O_RDWR);
    if(fd<0)
    {
        perror("open fail \n");
        return ;
    }else
    {
        printf("open /dev/hello success! \n");
		write(fd, "123456789009876543211", 21);
    }

    close(fd);
}
