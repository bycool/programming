#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main(){
	char* shmaddr = NULL;
	int shmid = -1;
	shmid = shmget((key_t)12345, 1024, IPC_CREAT| IPC_EXCL| 0600);
	if(shmid == -1){
		printf("get shmid fail\n");
		return -1;
	}
	shmaddr = shmat(shmid, 0, 0);
	if(shmaddr == (void*)-1){
		printf("at shmid fail\n");
		return -1;
	}

	strcpy(shmaddr, "1234567890");

	getchar();

	if(shmdt(shmaddr) == -1){
		printf("shmdt fail\n");
		return -1;
	}

	if(shmctl(shmid, IPC_RMID, 0) == -1){
		printf("shmid rm fail\n");
		return -1;
	}
	shmid = -1;

	return 0;
}
