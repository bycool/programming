#include <stdio.h>
#include <stdlib.h>

int main(){
	char buffer[32] = "rsync --daemon";
	printf("before rsync\n");
	system(buffer);
	printf("after rsync\n");
	
}
