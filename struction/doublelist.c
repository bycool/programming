#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *front, *next;
}node;

node* newnode(int val){
	node* new = (node*)malloc(sizeof(node));
	new->front = new;
	new->next = new;
	return new;
}

void insertnode(node** root, int val){
	printf("[%d]\n", val);
	if(*root == NULL){
		*root = newnode(val);
		return;
	}

	node* tmp = *root;
	node* new = newnode(val);
	while(tmp->next != *root){
		tmp = tmp->next;
	}
	tmp->next = new;
	new->front = tmp;
	new->next = *root;
}

void displayn(node* root){
	node* tmp = root;
	while(tmp->next != root){
		printf(".[%d]", tmp->val);
		tmp = tmp->next;
	}
	printf(".[%d]\n", tmp->val);
}

void displayf(node* root){
	node* tmp = root;
	while(tmp->front != root){
		printf(".[%d]", tmp->val);
		tmp = tmp->front;
	}
	printf(".[%d]\n", tmp->val);
}

#if 0
void destroy(node* root){
	if(root == NULL) return ;
	node* dnode = root-next;
	node* nnode = root->next;
	while(nnode->next != dnode){
		node-
	}
}
#endif

void main(){
	int arr[10] = {5,2,3,4,1,7,9,8,0,6};
	node* head = NULL;
	int i = 0;
	for(i=0; i<10; i++)
		insertnode(&head, arr[i]);

	displayn(head);
	displayf(head);
}
