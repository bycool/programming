#include <stdio.h>
#include <pthread.h>

pthread_t ntid;


void printids(const char* s){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n",s,(unsigned int)pid,(unsigned int)tid,(unsigned int)tid);
}

void *thr_fn(void *arg){
	printids("new pread:");
	return ((void*)0);
}

int create_main(){
	int err;
	err = pthread_create(&ntid,NULL,thr_fn,NULL);
	if(err != 0) printf("cant create pthread %d\n",strerror(err));
	printids("main thread:");
	sleep(1);
	return 0;
}
//=====================================================================
struct foo{
	int a,b,c,d;
};

void printfoo(const char* s,const struct foo *fp){
	printf(s);
	printf("foo.a = %d\n",fp->a);
	printf("foo.b = %d\n",fp->b);
	printf("foo.c = %d\n",fp->c);
	printf("foo.d = %d\n",fp->d);
}

void *thr_fn1(void* arg){
	struct foo foo = {1,2,3,4};
	printfoo("thread 1: \n", &foo);
	sleep(5);
	pthread_exit((void*)&foo);
}
void *thr_fn2(void *arg){
	printf("thread 2: id = %d\n",pthread_self());
	printf((void*)0);
}

int exit_main(){
	int err;
	pthread_t tid1,tid2;
	struct foo *fp;
	
	err = pthread_create(&tid1,NULL,thr_fn1,NULL); if(err != 0 ) printf("thread 1 err : %d\n",strerror(err));
	err = pthread_join(tid1,(void*)&fp); if(err != 0 ) printf("cant join thread 1: %d\n",strerror(err));
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2,NULL,thr_fn2,NULL); if(err != 0 ) printf("thread 2 err : %d\n",strerror(err));
	sleep(1);
	printfoo("parent:\n",fp);
	exit(0);
}

//=====================================================================
void cleanup(void* arg){
	printf("cleanup %s\n",(char*)arg);
}
void *pth_fn1(void *arg){
	printf("thread 1: start\n");
	pthread_cleanup_push(cleanup,"pthread 1 handler");
	printf("thread 1 push complete\n");
	if(arg) 
//		return ((void*)1);
		pthread_exit((void*)1);
	pthread_cleanup_pop(0);
	pthread_exit((void*)1);
//	return ((void*)1);
}
void cleanup_main(){
	int err ;
	pthread_t tid1,tid2;
	void* tret;
	
	err = pthread_create(&tid1,NULL,pth_fn1,((void*)1));

	sleep(1);
	
}






int main(void){
//	create_main();
//	exit_main();
	cleanup_main();

}




