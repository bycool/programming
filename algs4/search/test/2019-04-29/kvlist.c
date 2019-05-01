#include <stdio.h>
#include <stdlib.h>

typedef struct kvnode {
	int key;
	int val;
	struct kvnode* next;
}kvnode;


