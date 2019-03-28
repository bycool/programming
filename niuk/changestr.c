#include <stdio.h>
#include <string.h>



void replacestr(char* src, char* dst, char c, char* to){
	char* psrc = src;
	char* pdst = dst;

	while(*psrc != '\0'){
		if(*psrc != c ){
			*pdst++ = *psrc;
		}else{
			pdst += sprintf(pdst, "%s", to);
		}
		psrc++;
	}
	*pdst = 0;
}

int main(){
	char src[32] = "hello ni ha y";
	char dst[64] = { 0 };

	replacestr(src, dst, ' ', "%20");

	printf("dst:%s\n", dst);
}
