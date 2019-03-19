#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

unsigned char aes128_en(unsigned char* in, int len, unsigned char** out);
unsigned char aes128_de(unsigned char* in, int len);
