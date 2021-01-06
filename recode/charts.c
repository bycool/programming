#include <stdio.h>
#include <string.h>

void main(){
	char c[64] = "U8.444.6U8.ACT_FUNDACCOUNTJOUR.0U8.C1.2U8.C2.1";
	char* ps = NULL;
	ps = strchr(c, 1);
	if(ps)
	    printf("%s\n", ps);
}
