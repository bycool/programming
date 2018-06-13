
#include <stdio.h>

#define is_digit(c) ((c) >= '0' && (c) <= '9')

static int skip_atoi(const char **s)
{
    int i=0;

    while (is_digit(**s))
        i = i*10 + *((*s)++) - '0';
    return i;
}

void main(){
	const char *buf = {"12345"};
	int i = skip_atoi(&buf);
	printf("i:%d\n", i);
}
