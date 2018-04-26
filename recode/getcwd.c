#include <stdio.h>
#include <unistd.h>

int main(){
	char buffer[256] ;
	char* pwd = getcwd(buffer,256);
	printf("return*:%s:  %p\n",pwd,pwd);
	printf("buffer*:%s:  %p\n",buffer,buffer);
	return 0;
}

