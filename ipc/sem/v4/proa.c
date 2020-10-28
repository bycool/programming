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




int main(){
	int semval = -1;
	struct sembuf sem_g;
	struct sembuf sem_p;

	sem_g.sem_num = 0;  //which sem be set;  0 : the first one
	sem_g.sem_op = -1;  //the operation: -1, sem -1;  1, sem +1;
	sem_g.sem_flg = SEM_UNDO; // operation flag
	sem_p.sem_num = 0;
	sem_p.sem_op = 1;
	sem_p.sem_flg = SEM_UNDO;
	SEMUN semdel;
	int sem_id = semget(ftok(".", 's'), 32, IPC_CREAT | IPC_EXCL | 0600);
	if(sem_id == -1){ printf("semid get fail\n"); return -1; }
	printf("keys: %x, sem_id: %d\n", ftok(".",'s'), sem_id);

	SEMUN seminit;
	seminit.val = 1;
	if(semctl(sem_id, 0, SETVAL, seminit) == -1){
		printf("semid init fail\n");
		goto ret;
	}

	semval = semctl(sem_id, 0, GETVAL, 0);
	printf("semval: %d\n", semval);

	semop(sem_id, &sem_g, 1);
	semop(sem_id, &sem_g, 1);
	semval = semctl(sem_id, 0, GETVAL, 0);
	printf("semval: %d\n", semval);
	

ret:
	if(semctl(sem_id, 0, IPC_RMID, semdel) == -1){
		printf("semid rm fail\n");
		return -1;
	}
	return 0;
}
