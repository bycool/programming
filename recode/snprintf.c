#include <stdio.h>

int main(){
	int a = 0;
	char buf[10] = {1};
	a = snprintf(buf, 4, "%s", "abcdefg");
	printf("%d | %s\n",a, buf);
}
