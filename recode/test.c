#include <stdio.h>
#include <string.h>

void* change(long title){
	printf("%p\n",&title);
	return (void*)title;
}

int main(){
	long title = 1;
	char* tmp = change(title);
	printf("%lu\n", tmp);
	printf("%p\n", &tmp);
}
