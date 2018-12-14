#include <stdio.h>

#define CHAR_OFFSET 0

unsigned int get_checksum1(char *buf1, int len)
{
    int i;
    unsigned int s1, s2;
    char *buf = (char *)buf1;

    s1 = s2 = 0;
    for (i = 0; i < (len-4); i+=4) {
    s2 += 4*(s1 + buf[i]) + 3*buf[i+1] + 2*buf[i+2] + buf[i+3] +
      10*CHAR_OFFSET;
    s1 += (buf[i+0] + buf[i+1] + buf[i+2] + buf[i+3] + 4*CHAR_OFFSET);
    }
    for (; i < len; i++) {
    s1 += (buf[i]+CHAR_OFFSET); s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}


int main(){
	unsigned int sum = 0;
	char buf[64] = {"123456abcde123456abcdefghigklmnopqrstuvwxyzfghigklmnopqrstuvwxy"};
	int bl = 64;
	sum = get_checksum1(buf, bl);
	printf("sum: %u\n", sum);
}
