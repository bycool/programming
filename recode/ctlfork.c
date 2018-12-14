#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_exec(const char* cmd_buf, char* args_buf[]){
	pid_t pid;
	int status;

	pid = fork();
	if(pid == -1)
		return -1;
	if(pid > 0){
		wait(pid, &status, 0);
		exit(0);
	}else{
		execvp(cmd_buf, args_buf);
	}
	return 0;
}

int main(){
	char cmd[12] = "rsync";
	char* args[] = {"rsync", "-ar /home/ten/workstation /tmp/", NULL};
	cmd_exec(cmd, args);
}
