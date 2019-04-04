#include <stdio.h>
#include <stdlib.h>

typedef struct rnode {
	int key;
	int val;
	struct rnode* next;
}rnode;

rnode head = {0,0, NULL};

rnode* getrnode(rnode* head,int key){
	rnode* trnode = head;
	while(trnode!=NULL){
		if(trnode->key!=key){
			trnode = trnode->next;
			continue;
		}
		break;
//		printf("get.key:[%d],val:[%d]\n",trnode->key, trnode->val);
	}
	return trnode;
}

void put(rnode* head, int key, int val){
	rnode* thead = head;
	rnode* trnode = NULL;

	trnode = getrnode(head, key);
	if(trnode!=NULL){
		trnode->val = val;
		return;
	}

	trnode = (rnode*)malloc(sizeof(rnode));
	trnode->key = key;
	trnode->val = val;

	trnode->next = thead->next;
	thead->next = trnode;
	
}

void destroylist(rnode* head){
	rnode* thead = head->next;
	head->next = NULL;
	rnode* nnode = NULL;
	while(thead!=NULL){
		nnode = thead->next;
		free(thead);
		thead = nnode;
	}	
}

int get(rnode* node){
	return node->val;
}

void display(rnode* head){
	rnode* thead = head;
	while(thead!=NULL){
		printf("key:[%d],val:[%d]\n", thead->key, thead->val);
		thead = thead->next;
	}
}

int main(){
	int i = 0;
	for(i=1; i<20; i++)
		put(&head, i, i+1);

	put(&head, 0, 20);

	rnode* t = getrnode(&head, 15);
	
	printf("%d\n", get(t));

	display(&head);

	destroylist(&head);
}

