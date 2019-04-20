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

node* searchnode(node* root, int val){
	if(root==NULL) return NULL;

	node *tmp = root;

	if(val < root->val)
		searchnode(root->left, val);
	else if(val > root->val)
		searchnode(root->right, val);
	else if(val == root->val)
		return tmp;
	else
		return NULL;
}

void insertnode(node** root, int val){
	if(*root==NULL){
		*root = newnode(val);
		return ;
	}
	if(val < (*root)->val)
		insertnode(&((*root)->left), val);
	else
		insertnode(&((*root)->right),val);
}

node* findmax(node* root){
	if(root==NULL) return NULL;
	node* tmp = root;
	while(tmp->right){
		tmp = tmp->right;
	}
	return tmp;
}

node* findmin(node* root){
	if(root==NULL) return NULL;
	node* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

node* deletenode(node* root, int val){
	if(root==NULL) return;

	node* dnode = NULL;

	if(val < root->val)
		root->left = deletenode(root->left, val);
	else if(val > root->val)
		root->right = deletenode(root->right, val);
	else if(root->left && root->right){
		dnode = findmin(root->right);
		root->val = dnode->val;
		root->right = deletenode(root->right, root->val);
	}else{
		dnode = root;
		if(root->left == NULL) root = root->right;
		else if(root->right == NULL) root = root->left;
		printf("-[%d]\n", dnode->val);
		free(dnode);
	}
	return root;
}

void destroytree(node* root){
	if(root==NULL) return ;
	destroytree(root->left);
	destroytree(root->right);
	printf("-[%d]",root->val);
	free(root);
	root = NULL;
}

void midisplaytree(node* root){
	if(root==NULL) return ;
	midisplaytree(root->left);
	printf(".[%d]",root->val);
	midisplaytree(root->right);
}

int main(){
	int arr[5] = { 4,2,5,1,6 };
	node* root = NULL;
	int i = 0;
	for(i=0; i<5; i++)
		insertnode(&root, arr[i]);

	node* tmp = searchnode(root, 7);
	if(tmp){
		printf("search:%d\n",tmp->val);
	}

	midisplaytree(root);
	printf("\n");

	deletenode(root, 5);

	destroytree(root);
	printf("\n");

}
