#include <stdio.h>
#include <stdlib.h>

#define LENGTH(p)  ( (sizeof(p)) / (sizeof(p[0])) )

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

bnode* btree_insert(bnode* root, int val){
	if(root == NULL){
		root = newbnode(val);
	}else if(val<root->val){
		root->left = btree_insert(root->left, val);
	}else{
		root->right = btree_insert(root->right, val);
	}
	return root;
}

bnode* findmin(bnode* root){
	if(root == NULL) return NULL;

	bnode* p = root;
	while(p->left)
		p = p->left;
	return p;
}

bnode* btree_delete(bnode* root, int val){
	if(root == NULL) return NULL;

	if(val < root->val){
		root->left = btree_delete(root->left, val);
	}else if(val > root->val){
		root->right = btree_delete(root->right, val);
	}else if(root->left && root->right){
		bnode* min = findmin(root->right);
		root->val = min->val;
		root->right = btree_delete(root->right, root->val);
	}else{
		bnode* dnode = root;
		if(root->left)
			root = root->left;
		else
			root = root->right;

		free(dnode);
	}
	return root;
}

void ldr_display(bnode* root){
	if(root == NULL) return ;
	ldr_display(root->left);
	printf(".[%d]", root->val);
	ldr_display(root->right);
}

void destorytree(bnode* root){
	if(root == NULL) return ;
	destorytree(root->left);
	destorytree(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void main(){
	int arr[] = {6,1,3,8,5,0,7,9,2,4};
	int alen = LENGTH(arr);

	bnode* root = NULL;
	int i = 0;

	for(i=0; i<alen; i++)
		root = btree_insert(root, arr[i]);

	ldr_display(root);
	printf("\n");

	btree_delete(root, 5);

	ldr_display(root);
	printf("\n");

	destorytree(root);
	printf("\n");
}
