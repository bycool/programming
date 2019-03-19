#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>


typedef struct mdate {
	int i[10];
}mdate;

int main(int argc, char** argv){
	char ch = 0;
	int shmid = -1;
	mdate * mdate = NULL;
	int exit = -1;

	while((ch = getopt(argc, argv, "c:")) != -1){
		switch(ch){
			case 'c':
				exit = atoi(optarg);
				break;
			default:
				break;
		}
	}

	if(fork())
		_exit(0);

	shmid = shmget((key_t)9527, sizeof(mdate), IPC_CREAT | IPC_EXCL |0600);
	if (shmid < 0){
		shmid = shmget((key_t)9527, sizeof(mdate), 0600);
		if(shmid < 0){
			printf("shmget fail\n");
			return -1;
		}
	}

	mdate = shmat(shmid, 0, 0);
	mdate->i[0] = exit;

	while(mdate->i[0]){
		sleep(1);
		printf("exit: %d\n", mdate->i[0]);
	}

	shmdt(mdate);
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
