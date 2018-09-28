#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int prepend(char **buffer, int *buflen, const char* str, int namelen){
	*buflen -= namelen;
	if(*buflen < 0)
		return -1;
	*buffer -= namelen;
	memcpy(*buffer, str, namelen);
	return 0;
}

int main(){
	int len ;
	char buffer[10];
	prepend(&buffer, &len, "123",3);
}
