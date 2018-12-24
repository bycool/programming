#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main(){
	char readbuf[1024];
	char* shmaddr = NULL;
	int shmid = -1;
	shmid = shmget((key_t)12345, 1024, 0600);
	if(shmid == -1){
		printf("shmid fail\n");
		return -1;
	}
	shmaddr = shmat(shmid, 0, 0);
	if(shmaddr == (void*)-1){
		printf("shmat fail\n");
		return -1;
	}

	strcpy(readbuf, shmaddr);

	printf("readbuf: %s\n", readbuf);

	if(shmdt(shmaddr)==-1){
		printf("shmdt fail\n");
		return -1;
	}
	
	return 0;
}
