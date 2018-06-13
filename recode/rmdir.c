#include <stdio.h>

int main(){
	int rc = remove("./1.txt");
	if(rc == 0){
		printf("remove file\n");
	}else{
		printf("remove file fail\n");
	}
}
