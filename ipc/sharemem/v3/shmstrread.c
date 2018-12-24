#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#include "shmstr.h"

int main(){
	mdate *mdate = NULL;
	int shmid = -1;
	shmid = shmget((key_t)12345, sizeof(mdate), 0600);
	if(shmid == -1){
		printf("shmget fail\n");
		return -1;
	}
	mdate = shmat(shmid, 0, 0);
	if(mdate == NULL){
		printf("shmat fail\n");
		return -1;
	}

	printf("szc:%s\n", mdate->czs);
	printf("year:%d\n", mdate->year);
	printf("month:%d\n", mdate->month);
	printf("day:%d\n", mdate->day);

	if(shmdt(mdate) == -1){
		printf("shmdt fail\n");
		return -1;
	}

	return 0;
}

