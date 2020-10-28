#include <stdio.h>
#include <string.h>

void main(){
	char* buf = "Your lips are smoother than vaseline\n";
	int len = strlen(buf);
	int i = 0;
	for(i=0; i<len; i++){
		printf("%c:%02x\n", buf[i],buf[i]);
	}
//	printf("\n");
}
