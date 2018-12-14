#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int counstrlen(char* str){
	char* p = NULL;
	int newlen = 0;

	newlen = strlen(str)+1; // + '\0'
	p = str;
	while(*p){
		if(*p == ' ')
			newlen += 2;
		p++;
	}
	return newlen;
}

int main(){
	char* p = NULL;
	char* np = NULL;
	char strrc[64] = "hello world ! it's sucks, but real";
	int newlen = counstrlen(strrc);

	char* newstr = (char*)malloc(newlen);
	p = strrc;
	np = newstr;
	while(*p){
		if(*p == ' '){
			*np++ = '%';
			*np++ = '2';
			*np++ = '0';
		}else{
			*np++ = *p;
		}
		p++;
	}
	printf("%s\n", newstr);
}

