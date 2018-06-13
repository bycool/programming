#include <stdio.h>

int main(){
	char buf[18] = {"cccccccccccccccc1"};
	buf[17] = 0;
	printf("%s\n",buf);
}
