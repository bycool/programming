#include <stdio.h>
#include <string.h>

int main(){
	char buf[32] = "abcd";
	int ret = sprintf(buf, "%s%s", buf, "abc");
	printf("%d:%d: %s\n",ret, strlen(buf), buf);
}
