/*
 *  *  fork_test.c
 *   *  version 1
 *    *  Created on: 2010-5-29
 *     *      Author: wangth
 *      */
#include <unistd.h>
#include <stdio.h> 
	int count=0;
int main () 
{ 
	int if_s = 1;
	pid_t fpid; //fpid表示fork函数返回的值
	printf("befor fork\n");
	fpid=fork(); 
	if (fpid < 0)
	{
		printf("error in fork!"); 

	}
	else if (fpid == 0)
	{
		printf("i am the child process, my process id is %d\n",getpid());
		if_s = 0;
	}
	else
	{
		printf("parent printf fpid:%d\n", fpid);
		printf("i am the parent process, my process id is %d\n",getpid());
		//_exit(0);
	}
	printf("pid: %d, if_s: %d\n", getpid(), if_s);
	return 0;
}
