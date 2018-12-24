#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>

#define BUF_SIZE 4096

int main()
{
    void *shm_addr = NULL;
    char buffer[BUF_SIZE];

    int shmid;
    // 使用约定的键值创建共享内存
    shmid = shmget((key_t) 1234,  BUF_SIZE, 0666 | IPC_CREAT);
    printf("shmid : %u\n", shmid);
    if (shmid < 0)
    {
        perror("shmget error!");
        exit(1);
    }

    // 将共享内存附加到本进程
    shm_addr = shmat(shmid, NULL, 0);
    if (shm_addr == (void *) -1)
    {
        perror("shmat error!");
        exit(1);
    }

    // 写入数据
    bzero(buffer, BUF_SIZE);
    sprintf(buffer, "Hello, My PID is %u\n", (unsigned int) getpid());
    printf("send data: %s\n", buffer);

    memcpy(shm_addr, buffer, strlen(buffer));

    sleep(5);

    // 分离
    if (shmdt(shm_addr) == -1)
    {
        printf("shmdt error!\n");
        exit(1);
    }
}
