#include <stdio.h>
#include <string.h>

void change(char* title){
	printf("%d\n",strlen(title));
}

int main(){
	char title[10] = {"nihaoy"};
	change(title);
	printf("%d\n",title);
}
