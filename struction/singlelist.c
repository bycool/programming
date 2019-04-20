#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
}node;

node* newnode(int val){
	node* rc = (node*)malloc(sizeof(node));
	rc->val = val;
	rc->next = NULL;
	return rc;
}

void insertnode(node** root, int val){
	if(*root == NULL){
		*root = newnode(val);
		return ;
	}

	node* tmp = *root;
	while(tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = newnode(val);
}

void display(node* root){
	if(root == NULL) return ;
	node* tmp = root;
	while(tmp){
		printf(".[%d]", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

void deletenode(node** root, int val){
	if(root == NULL) return ;
	node* fnode = *root;
	node* dnode = NULL;

	if((*root)->val == val){
		dnode = *root;
		*root = (*root)->next;
		printf("-[%d]\n", dnode->val);
		free(dnode);
		return ;
	}

	while(fnode){
		dnode = fnode->next;
		if(dnode->val == val){
			fnode->next = dnode->next;
			printf("-[%d]\n", dnode->val);
			free(dnode);
			break ;
		}
		fnode = dnode;
	}
}

void destroy(node* root){
	if(root == NULL) return ;
	node* tmp = root;
	node* dnode = NULL;

	while(tmp){
		dnode = tmp;
		tmp = tmp->next;
		printf("-[%d]", dnode->val);
		free(dnode);
	}
	printf("\n");
}

void main(){
	int arr[10] = {6,3,1,2,4,7,9,0,5,8};
	int i = 0;
	node* head = NULL;
	for(i=0; i<10; i++){
		insertnode(&head, arr[i]);
	}
	display(head);

	deletenode(&head, 4);
	display(head);

	deletenode(&head, 6);
	display(head);

	destroy(head);

}
