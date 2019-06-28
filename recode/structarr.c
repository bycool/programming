#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int id;
	char path[1024];
	struct node* next;
}node;

void main() {
	node* n1 = (node*)malloc(sizeof(node));
	n1->id = 1;
	strcpy(n1->path, "/home/ten/t1");
	n1->next = NULL;

	printf("id:   %d\n", n1->id);
	printf("path: %s\n", n1->path);
}
