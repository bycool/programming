#include <stdio.h>
#include <time.h>

int main(){
	long tim = time(0);
	struct tm *p;
	p = gmtime(&tim);
    char s[100];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
    printf("%d: %s\n", (int)tim, s);
	return 0;
}
