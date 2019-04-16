#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	int val;
	struct node *next;
}node;

node* newnode(int key, int val){
	node *rc = (node*)malloc(sizeof(node));
	rc->key = key;
	rc->val = val;
	rc->next = NULL;
	return rc;
}

node* getnode(node* head, int key){
	if(head==NULL) return NULL;
	node* tmp = head;

	while(tmp){
		if(tmp->key == key)
			break;
		tmp = tmp->next;
	}
	return tmp;
}

void insertnode(node** head, int key, int val){
	if(*head == NULL){
		*head = newnode(key, val);
		return ;
	}

	node* tmp = NULL;
	tmp = getnode(*head, key);
	if(tmp){
		tmp->val = val;
		return;
	}

	tmp = *head;
	while(tmp->next){
		tmp = tmp->next;
	}
	tmp->next = newnode(key, val);
}

void deletenode(node* head, int key){
	if(head == NULL) return ;

	node* dnode = NULL;
	node* nnode = NULL;
	dnode = getnode(head, key);
	if(!dnode)
		return ;

	nnode = dnode->next;
	if(!nnode){
		free(dnode);
	}else{
		dnode->key = nnode->key;
		dnode->val = nnode->val;
		dnode->next = nnode->next;
		free(nnode);
	}
}

void displaynodes(node* head){
	if(head == NULL) return ;

	node* tmp = head;
	while(tmp){
		printf(" [%d|%d]", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

void destroynodes(node* head){
	if(head == NULL) return ;

	node* dnode = head;
	node* nnode = NULL;

	while(dnode){
		nnode = dnode->next;
		printf(".[%d|%d]", dnode->key, dnode->val);
		free(dnode);
		dnode = nnode;
	}
	printf("\n");
}

void main(){
	node* head = NULL;
	int i = 0;
	for(i=0; i<10; i++)
		insertnode(&head, i, i+1);

	deletenode(head, 5);

	displaynodes(head);

	destroynodes(head);

}






