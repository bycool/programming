#include <stdio.h>
#include <string.h>

int bf(char* src, char* tgt){
	int i = 0, j = 0;
	int sl = strlen(src);
	int tl = strlen(tgt);

	printf("sl: %d, tl: %d\n", sl, tl);

	while(i<sl && j<tl){
		if(src[i] == tgt[j]){
			i++;
			j++;
		}else{
			i = i-j+1;
			j = 0;
		}
	}
	if(tl == j)
		return i-j;
	else
		return -1;
}

void main(){
	char src[] = "abcdefgsgeilisjifes";
    char tgt[] = "gsgei";

    int rc = bf(src, tgt);
    printf("rc: %d\n", rc);
}
