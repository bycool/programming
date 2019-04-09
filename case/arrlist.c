#include <stdio.h>
#include <stdlib.h>

typedef struct lnode {
	int key;
	int val;
	struct lnode* next;
}lnode;

lnode* newlnode(int key, int val){
	lnode* rc = (lnode*)malloc(sizeof(lnode));
	rc->key = key;
	rc->val = val;
	rc->next= NULL;
	return rc;
}

lnode* getlnode(lnode** head, int key){
	lnode* tmp = *head;
	while(tmp){
		if(tmp->key != key){
			tmp = tmp->next;
			continue;
		}
		break;
	}
	return tmp;
}

void put(lnode** head, int key, int val){
	lnode* tmp = NULL;
	lnode* nlnode = NULL;

	if(!(*head)){
		*head = newlnode(key, val);
		return;
	}

	tmp = getlnode(head, key);
	if(tmp){
		tmp->val = val;
		return;
	}

	nlnode = newlnode(key, val);

	nlnode->next = (*head)->next;
	(*head)->next = nlnode;
}

void destroylist(lnode* head){
	lnode* dnode = head;
	lnode* tnode = NULL;
	while(dnode){
		tnode = dnode->next;
		printf(".[%d|%d]",dnode->key, dnode->val);
		free(dnode);
		dnode = tnode;
	}
	printf("\n");
}

void displaylist(lnode* head){
	lnode* tmp = head;
	while(tmp){
		printf("[%d|%d]", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

int main(){
	int i = 0;
	lnode* head = NULL;
	for(i=0; i<20; i++)
		put(&head, i, i+1);

	displaylist(head);

	destroylist(head);
}
