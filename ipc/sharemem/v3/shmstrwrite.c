#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include "shmstr.h"

int main(){
	mdate* mdate = NULL;
	int shmid = -1;
	shmid = shmget((key_t)12345,  sizeof(mdate), IPC_CREAT | IPC_EXCL | 0600);
	if(shmid == -1){
		printf("shmget fail\n");
		return -1;
	}
	mdate=shmat(shmid, 0, 0);
	if(mdate == NULL){
		printf("shmat fail\n");
		return -1;
	}

	strcpy(mdate->czs, "zhu");
	mdate->year = 2018;
	mdate->month = 12;
	mdate->day = 14;

	getchar();

	if(shmdt(mdate) == -1){
		printf("shmdt fail\n");
		return -1;
	}

	if(shmctl(shmid, IPC_RMID, 0)){
		printf("shmctl rm fail\n");
		return -1;
	}

	return 0;
}
