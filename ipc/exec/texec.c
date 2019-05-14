#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>


void* threade(){
	
	pid_t pid = getpid();
	printf("pthread.pid:%d\n", pid);

	char cmd[8] = "rsync";
	//char *argvs[] = {"./test","-avzr","/home/ten/t2/","--delete", "--port", "9878", "2000",  "root@192.168.0.22::path2_1", "&>/dev/null", NULL};
	char *argvs[] = {"rsync","-avzr", "/home/ten/t2/", "--delete", "--port", "9878",  "root@192.168.253.163::path1_3", "&>/dev/null", NULL};

	int i = 5;
	int ret_state = 0;

	pid = fork();
	if(pid == 0){
		printf("child.pid: %d\n", getpid());
		execv(cmd, argvs);
		exit(10);
	}else if(pid >0){
		printf("p.child.pid: %d\n", pid);
		waitpid(pid, &ret_state, 0);
		while(i--){
			printf("main\n");
			sleep(1);
		}
	}
}

void main(){
	printf("main.paid: %d\n", getpid());
	pthread_t t1;
	pthread_create(&t1, NULL, threade, NULL);
	pthread_join(t1, NULL);
	while(1){
		printf("main\n");
		sleep(1);
	}
	pthread_exit(NULL);
}


