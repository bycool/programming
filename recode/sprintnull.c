#include <stdio.h>
#include <string.h>
int main(){
	char buf[10] = {"(null)"};
	printf("%d\n", strlen(buf));
	printf("%s\n", buf);
	char str[32] = "";
	sprintf(str, "%s", buf);
	printf("str: %s\n", str);
}
