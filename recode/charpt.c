#include <stdio.h>

void getbuf(char* buf){
	char tmp[32] = {"nihoa"};
	memcpy(buf, tmp, 32);
}

int main(){
	char buf[32] = {0};
	getbuf(buf);
	printf("%s\n", buf);
	
}
