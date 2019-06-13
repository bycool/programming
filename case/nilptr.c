#include <stdio.h>

typedef struct node {
	int i;
	struct node* next;
}node;

void main(){
	node* head = NULL;
	if(head->next == NULL)
		printf("null\n");
	else
		printf("2\n");
}
