/*
 * 二叉查找树
 */

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

void insertnode(node** root, int val){
	if(*root == NULL){
		*root = newnode(val);
		return ;
	}

	if (val < (*root)->val){
		insertnode(&((*root)->left), val);
	}else{
		insertnode(&((*root)->right), val);
	}
}

node* searchnode(node* root, int val){
	if(root == NULL) return NULL;

	node* tmp = root;
	if (val < tmp->val)
		searchnode(tmp->left, val);
	else if (val > tmp->val)
		searchnode(tmp->right, val);
	else if (val == tmp->val)
		return tmp;
	else
		return NULL;
}

node* findmin(node* root){
	if(root == NULL) return NULL;
	node* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

node* findmax(node* root){
	if(root == NULL) return NULL;
	node* tmp = root;
	while(tmp->right)
		tmp = tmp->right;
	return tmp;
}

node* deletenode(node* root, int val){
	if(root == NULL) return NULL;

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
		else if(root->right == NULL) root= root->left;
		printf("-[%d]\n", tmp->val);
		free(tmp);
	}
	return root;
}

void midisplay(node* root){
	if(root == NULL) return ;
	midisplay(root->left);
	printf(".[%d]", root->val);
	midisplay(root->right);
}

void destroy(node* root){
	if(root == NULL) return ;
	destroy(root->left);
	destroy(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void main(){
	int arr[10] = {7,8,5,9,2,4,1,3,6,0};
	int i = 0;
	node* root = NULL;
	for(i=0; i<10; i++){
		insertnode(&root, arr[i]);
	}

	node* tmp = findmin(root);
	printf("min:%d\n", tmp->val);
	tmp = findmax(root);
	printf("max:%d\n", tmp->val);


	midisplay(root);
	printf("\n");
	deletenode(root, 4);
	midisplay(root);
	printf("\n");
	destroy(root);
	printf("\n");

}
