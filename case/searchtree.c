#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *left, *right;
}node;

node* newnode(int val){
	node* rc = (node*)malloc(sizeof(node));
	rc->val = val;
	return  rc;
}

void insnode(node** head, int val){
	node* tmp = *head;
	if(*head==NULL){
		*head = newnode(val);
		return;
	}
	if(val < tmp->val)
		insnode(&(tmp->left), val);
	if(val > tmp->val)
		insnode(&(tmp->right), val);
}

void midisplay(node* head){
	if(head->left)
		midisplay(head->left);
	printf("[%d]", head->val);
	if(head->right)
		midisplay(head->right);
}

void destroytree(node* head){
	if(head->left)
		destroytree(head->left);
	if(head->right)
		destroytree(head->right);

	free(head);
	head=NULL;
}

node* searchnode(node* head, int val){
	if(head == NULL) return NULL;

	node* tmp = head;

	if(val < tmp->val)
		tmp = searchnode(tmp->left, val);
	else if(val > tmp->val)
		tmp = searchnode(tmp->right, val);

	return tmp;
}

node* findmin(node* head){
	node* tmp= head;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

node* findmax(node* head){
	node* tmp = head;
	while(tmp->right)
		tmp = tmp->right;
	return tmp;
}

node* delnode(node* head, int val){
	if(head==NULL) return NULL;

	node* tmp = NULL;

	if(val < head->val){
		head->left = delnode(head->left, val);
	}else if( val > head->val) {
		head->right = delnode(head->right, val);
	}else if(head->left && head->right){
		tmp = findmin(head->right);
		head->val = tmp->val;
		head->right = delnode(head->right, head->val);
	}else{
		tmp = head;
		if(head->left == NULL)
			head = head->right;
		else if(head->right == NULL)
			head = head->left;
		free(tmp);
	}
	return head;
}


int main(){
	node* head = NULL;
	int arr[15] = { 5,2,3,1,6, 4,10,15,13,17, 62,23,12,91,88};
	int i;
	for(i=0; i<15; i++)
		insnode(&head, arr[i]);

	midisplay(head);
	printf("\n");

	node* tmp = searchnode(head, 15);
	tmp->val = 16;

	tmp = findmin(head);
	printf("min:%d\n", tmp->val);
	tmp = findmax(head);
	printf("max:%d\n", tmp->val);

	delnode(head, 16);


	
	midisplay(head);
	printf("\n");

	destroytree(head);
}
