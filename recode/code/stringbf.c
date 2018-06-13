#include <stdio.h>

int stringbf(char* str, char* sub){
	int bas = 0, pos = 0;
	while(str[bas+pos]!='\0' && sub[pos]!='\0'){
		if(str[bas+pos] == sub[pos]){
			pos++;
		}else{
			pos = 0;
			bas++;
		}
	}
	if(sub[pos]=='\0'){
		return bas+1;
	}else{
		return -1;
	}
}

int main(){
	char str[] = "abcdefghigklmn";
	char sub[] = "def";
	int ret = stringbf(str,sub);
	printf("%d\n",ret);
}
