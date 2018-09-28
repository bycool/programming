#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tmalloc(char** tmp){
	*tmp = (char*)malloc(100);
	memcpy(*tmp, "111111111111111111111111", 100);
}

int main(){
	char *tmp = NULL;
	tmalloc(&tmp);
	printf("%s\n", tmp);
	free(tmp);
}
