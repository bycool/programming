#include <stdio.h>
#include <stdlib.h>

typedef struct bnode {
	int val;
	struct bnode *left, *right;
}bnode;

bnode* newbnode(int val){
	bnode* new = (bnode*)malloc(sizeof(bnode));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void insertbnode(bnode **head, int val){
	if(*head == NULL){
		*head = newbnode(val);
		return ;
	}

	if(val < (*head)->val)
		insertbnode(&((*head)->left), val);
	else
		insertbnode(&((*head)->right), val);
}

bnode* findmin(bnode* root){
	if(root == NULL) return NULL;
	bnode* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}


bnode* deletenode(bnode* root, int val){
	if(root == NULL) return NULL;

	if(val < root->val){
		root->left = deletenode(root->left, val);
	}else if(val > root->val){
		root->right = deletenode(root->right, val);
	}else if( root->left && root->right){
		bnode* tmp = findmin(root->right);
		root->val = tmp->val;
		root->right = deletenode(root->right, root->val);
	}else{
		bnode* dnode = root;
		if(root->left == NULL) root = root->right;
		else if(root->right == NULL) root = root->left;
		free(dnode);
	}
	return root;
}



void ldr_display(bnode* head){
	if(head == NULL) return;
	ldr_display(head->left);
	printf(".[%d]", head->val);
	ldr_display(head->right);
}

void destroytree(bnode* head){
	if(head == NULL) return;
	destroytree(head->left);
	destroytree(head->right);
	printf("-[%d]", head->val);
	free(head);
}

void main(){
	int arr[10] = {6,2,4,1,5,8,0,7,9,3};
	int i = 0;
	bnode* tree = NULL;

	for(i=0; i<10; i++)
		insertbnode(&tree, arr[i]);

	ldr_display(tree);
	printf("\n");

	deletenode(tree, 8);

	ldr_display(tree);
	printf("\n");

	destroytree(tree);
	printf("\n");
}
