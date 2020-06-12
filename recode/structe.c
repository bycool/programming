#include <stdio.h>

struct typeb {
	char* path;
//	short node_type;
};

void main(){
	printf("sizeof(typeb): %d\n", sizeof(struct typeb));
}
