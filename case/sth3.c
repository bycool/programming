#include <stdio.h>

void figure_to_bytes(char* str, int size, unsigned long num)
{
	printf("%d,%u\n",size,num);
    int i = 0;

    for (i = 0; i < size; ++i){
        str[i] = (unsigned char)((num << (8 * i)) >> ((size - 1) * 8));
/*
 *    str[0] ( (15<<(8*0))>>((4-1)*8) ) : 15>>24    
 *    00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001111 >>24
 */
		printf("%d\n",str[i]);
	}
	printf("----------\n");
}

unsigned long FDS_Build_Bytes_TO_Figure(unsigned char *str, int byte)
{
    int i;
    unsigned long result = 0;
    if(str == NULL || byte < 1)
    {
        return -1;
    }

    for(i = 0; i < byte; i ++)
    {
        result += ((unsigned long)str[i]) << (8 * (byte - 1 - i));
    }
    return result;
}


int main(){
	char str[20]={0};
	int size = 4;
	unsigned long num = 1555555; //8byte = 64bit
	/*
 *  2 : 00000000 00000000 00000000 00000000 00000000 00010111 10111100 01100011
 *	16: 0x0017bc63                                   23		  -68		99
 */
	printf("16:%x\n",num);
	printf("sizeof ul: %d\n",sizeof(num));
	figure_to_bytes(str,size,num);
	unsigned long test = FDS_Build_Bytes_TO_Figure(str,size);
	printf("%d\n",test);
	
}
