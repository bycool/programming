#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct _tab_op {
	unsigned int hv;
	unsigned int idx;
	struct _tab_op *l, *r;
}TAB_OP;

unsigned int sdbmhash(char *str){  
    unsigned int  hash =  0 ;  
   
    while(*str){   
        hash = (*str++) + (hash << 6 ) + (hash <<  16 ) - hash;  
    }  
    return  (hash &  0x7FFFFFFF );  
}

TAB_OP* root = 0;

void inssert(TAB_OP* new){

}

void main(){
	int i = 0;
	char* str[6] = {"abcd.ttt", "efgh.tttt", "1231as.ttt", "swjyu.tttt", "oiut.tttttt", "trtf.ttttttt"};
	for(i=0; i<6; i++)
		printf("keys: %u\n", sdbmhash(str[i]));

	//printf("str[%d]: %s\n", i, str[i]);
}
