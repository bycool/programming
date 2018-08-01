#include <stdio.h>

int main(){
	char buf[64] = "";
	sprintf(buf,"%s", "1\n2");
	printf("%s\n",buf);
}
