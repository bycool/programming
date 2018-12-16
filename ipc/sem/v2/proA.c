#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short* arry;
};

void writenum(int num){
	int fd = open("1.txt", O_CREAT|O_WRONLY|O_APPEND, 0666);
	char buf[32];
	sprintf(buf, ".%d.", num);
	write(fd, buf, strlen(buf));
	close(fd);
}

int main(){
	int sem_id = semget(ftok(".",'s'), 1, IPC_CREAT|IPC_EXCL|0666);
	if(sem_id == -1){ printf("get err:%m\n"); return -1;}

	union semun sem_union;
	sem_union.val = 1;
	semctl(sem_id, 0, SETVAL, sem_union);

    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;//P()
    sem_b.sem_flg = SEM_UNDO;
    struct sembuf sem_p;
    sem_p.sem_num = 0;
    sem_p.sem_op = 1;//V()
    sem_p.sem_flg = SEM_UNDO;


	int i = 0;
	for(i = 0; i < 10; ++i){
		semop(sem_id, &sem_b, 1);
		writenum(i);
		sleep(rand() % 3);
		writenum(i);
		sleep(rand() % 2);
		semop(sem_id, &sem_p, 1);	
	}

	sleep(10);

	union semun sem_del;
	semctl(sem_id, 0, IPC_RMID, sem_del);

	return 0;
}
