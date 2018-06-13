#include <stdio.h>

int stringbf(char* str, char* sub){
	int bas = 0, pos = 0;
	for(bas = 0; str[bas+pos]!='\n' && sub[pos]!='\0';bas++){
		if(str[bas+pos]==sub[pos]){
			pos++;
			bas--;
		}else{
			pos=0;
		}
	}
	if(sub[pos]=='\0'){
		printf("%d\n",bas+1);	return bas+1;
	}else
		return -1;
}

int main(){
	char str[15] = "abcdefefegd";
	char sub[4] = "feg";
	stringbf(str,sub);
}
