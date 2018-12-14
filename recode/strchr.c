#include <stdio.h>
#include <string.h>

int main(){
	char path[1024] = "/home/ten/source/src/fds_full_dll/.svn/tmp/props";
	char *p = NULL;
	char *tmp = path;
	while((p=strchr(tmp, '/')) != NULL) {
		if( p[1] != '\0')
			tmp = p+1;
		else
			break;
	}
	printf("%s\n", tmp);
}
