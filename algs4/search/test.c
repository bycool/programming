#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *left, *right;
}node;

node* newnode(int val){
	node *rc = (node*)malloc(sizeof(node));
	rc->val = val;
	rc->left = NULL;
	rc->right = NULL;
	return rc;
}

void insertnode(node **root, int val){
	if(*root==NULL){
		*root = newnode(val);
		return ;
	}

	if((*root)->val > val){
		insertnode(&((*root)->left), val);
	}else{
		insertnode((&(*root)->right), val);
	}
}

node* findmin(node* root){
	if(root==NULL) return NULL;

	node* tmp = root;
	while(tmp->left != NULL){
		tmp = tmp->left;
	}
	return tmp;
}

node* deletenode(node* root, int val){
	if(root==NULL) return ;

	node* tmp = NULL;

	if(val < root->val){
		root->left = deletenode(root->left, val);
	}else if(val > root->val){
		root->right = deletenode(root->right, val);
	}else if(root->left && root->right){
		tmp = findmin(root->right);
		root->val = tmp->val;
		root->right = deletenode(root->right, root->val);
	}else{
		tmp = root;
		if(root->left == NULL) root = root->right;
		else if(root->right == NULL) root = root->left;
		printf("del:%d\n", tmp->val);
		free(tmp);
	}
	return root;
}

void midisplay(node* root){
	if(root==NULL) return;
	midisplay(root->left);
	printf(" [%d]", root->val);
	midisplay(root->right);
}

void destroy(node* root){
	if(root==NULL) return;
	destroy(root->left);
	destroy(root->right);
	printf("-[%d]", root->val);
	return ;
}

void main(){
	int i = 0;
	node* root = NULL;
	int arr[5] = { 8,4,1,9,3};

	for(i=0;i<5;i++)
		insertnode(&root, arr[i]);

	midisplay(root);
	printf("\n");

	deletenode(root, 1);

	midisplay(root);
	printf("\n");

	destroy(root);
	printf("\n");
}



