#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef union semun {
    int val;
    struct semid_ds *buf;
    unsigned short* arry;
}SEMUN;

struct sembuf sem_g;

struct sembuf sem_p;

void writenum(int num){
    char buf[32];
    int fd = open("1.txt", O_CREAT | O_WRONLY | O_APPEND, 0600);
	sprintf(buf, ".%d.", num);
	write(fd, buf, strlen(buf));
	close(fd);
}

int main(){
	sem_g.sem_num = 0;
	sem_g.sem_op = -1;
	sem_g.sem_flg = SEM_UNDO;
	sem_p.sem_num = 0;
	sem_p.sem_op = 1;
	sem_p.sem_flg = SEM_UNDO;
	SEMUN semdel;
	int sem_id = semget(ftok(".", 's'), 1, IPC_CREAT | IPC_EXCL | 0600);
	if(sem_id == -1){ printf("semid get fail\n"); return -1; }

	SEMUN seminit;
	seminit.val = 1;
	if(semctl(sem_id, 0, SETVAL, seminit) == -1){
		printf("semid init fail\n");
		goto ret;
	}

	int i = 0;
	for(i=0; i<30; i++){
		semop(sem_id, &sem_g, 1);
		writenum(i);
		sleep(rand()%3);
		writenum(i);
		semop(sem_id, &sem_p, 1);
		sleep(rand()%2);
	}

ret:
	if(semctl(sem_id, 0, IPC_RMID, semdel) == -1){
		printf("semid rm fail\n");
		return -1;
	}
	return 0;
}
