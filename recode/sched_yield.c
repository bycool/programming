#include <sched.h>
#include <stdio.h>
#include <sys/time.h>


int getrandom(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec%4;
}


int main(){
	while(1){
		if(getrandom()==3){
			printf("give up time pic1\n");
			sched_yield();
			printf("give up time pic2\n");
		}else{
			printf("not 3\n");
			sleep(5);
			printf("not 3+5\n");
		}
	}
}
