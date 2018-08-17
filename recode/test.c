#include <stdio.h>
#include <string.h>

void change(char* title){
	printf("%d\n",strlen(title));
}

int main(){
	char title[1024*5] = {"nihaoy"};
	change(title);
	printf("%d\n",title);
	printf("%d\n", sizeof(title));
}
