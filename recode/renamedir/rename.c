#include <stdio.h>

int main(){
	char old_dir[8] = {"1"};
	char new_dir[8] = {"2"};
	if(rename(old_dir,new_dir)==0){
		printf("rename done\n");
	}
}
