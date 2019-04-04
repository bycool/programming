#include <stdio.h>
#include <string.h>


void replacestr2(char* str, int length){
 if(str==NULL)
            return;
        char* pstr = str;
        char* nstr = str;
        int newlen = length;
        while(*pstr != '\0'){
            if(*pstr == ' ')
                newlen +=2;
            pstr++;
        }
		printf("%d:%d\n", length, newlen);
        if(newlen<length)
            return;
        
        pstr = str+length;
        nstr = str+newlen;
        while(pstr!=str && nstr!=str){
            if(*pstr != ' '){
                *nstr-- = *pstr--;
            }else{
                *nstr-- = '0';
                *nstr-- = '2';
                *nstr-- = '%';
                pstr--;
            }
        }

}


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
	char src[32] = {"hello ni ha y"};
	char dst[64] = { 0 };

	replacestr2(src, strlen(src));
	printf("%s\n", src);

//	replacestr(src, dst, ' ', "%20");

//	printf("dst:%s\n", dst);
}
