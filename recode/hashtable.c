#include <stdio.h>
#include <stdlib.h>

#define debug 0

#define hashlen 5120

typedef struct hnode {
	int data;
	struct hnode* next;
}hnode;

static struct hnode **hashtable = 0;

int main(){
	int i = 0;
	hashtable = (struct hnode**)malloc(sizeof(struct hnode*)*hashlen);

#if debug
	printf("sizeof hnode* :%d\n", sizeof(struct hnode*));
	printf("sizeof hnode  :%d\n", sizeof(struct hnode));
	printf("sizeof void*  :%d\n", sizeof(void*));
#endif	

	for(i=0; i<hashlen; i++) hashtable[i] = 0;

	struct hnode* tmpnode = (struct hnode*)malloc(sizeof(struct hnode));
	tmpnode->data = 1;
	tmpnode->next = hashtable[1];
	hashtable[1] = tmpnode;

	printf("hashtable[1].data: %d\n", hashtable[1]->data);

}
