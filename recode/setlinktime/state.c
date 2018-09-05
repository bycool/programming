#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


int main(){
	struct stat fdst;
	struct tm *p;
	char s[100];

	stat("1.txt.link", &fdst);
	p = gmtime(&fdst.st_atime);
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
	printf("atime: %s\n",s);
	printf("mtime: %lu\n",fdst.st_mtime);
	
	
}
