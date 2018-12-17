#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
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
    sprintf(buf, "|%d|", num);
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
	int sem_id = semget(ftok(".", 's'), 1, 0666);
	if(sem_id == -1){ printf("sem_id get fail\n"); return -1; }

	int i = 0;
	for(i=0; i<20; i++){
		semop(sem_id, &sem_g, 1);
		writenum(i);
		sleep(rand()%3);
		writenum(i);
		semop(sem_id, &sem_p, 1);
		sleep(rand()%2);
	}
	return 0;
}
