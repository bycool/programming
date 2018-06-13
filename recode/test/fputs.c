#include <stdio.h>
#include <fcntl.h>

int main(){
	char buf[32];
	FILE *fd = fopen("./1.txt","a+");
	scanf("%s",buf);
	fputs(buf,fd);
	fclose(fd);
	
}
