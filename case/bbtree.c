#include <stdio.h>
#include <stdlib.h>

typedef struct bnode {
	int key;
	int val;
	struct bnode *lnode, *rnode;
}bnode;

bnode* newbnode(int key, int val){
	bnode* rt = (bnode*)malloc(sizeof(bnode));
	rt->key = key;
	rt->val = val;
	rt->lnode = NULL;
	rt->rnode = NULL;
	return rt;
}

void insertobtree(bnode **root, int key, int val){
	if(*root == NULL){
		*root = newbnode(key, val);
		return;
	}

	bnode* nnode = (bnode*)malloc(sizeof(bnode));
	nnode->key = key;
	nnode->val = val;
	nnode->lnode = NULL;
	nnode->rnode = NULL;

	if((*root)->key > key){
		if((*root)->lnode == NULL){
			(*root)->lnode = nnode;
		}else{
			free(nnode);
			insertobtree(&((*root)->lnode), key, val);
		}
	}else{
		if((*root)->rnode == NULL){
			(*root)->rnode = nnode;
		}else{
			free(nnode);
			insertobtree(&((*root)->rnode), key, val);
		}
	}
}

void deletebnode(bnode **root, int key){

}

void destroybtree(bnode *root){
	if(root!=NULL){
		if(root->lnode!=NULL){
			destroybtree(root->lnode);
			root->lnode = NULL;
		}
		if(root->rnode!=NULL){
			destroybtree(root->rnode);
			root->rnode = NULL;
		}

		printf("d[%d|%d]", root->key, root->val);
		free(root);
		root=NULL;
	}
}

void midisplaytree(bnode *root){
	if(root->lnode != NULL)
		midisplaytree(root->lnode);
	printf("[%d|%d],", root->key, root->val);
	if(root->rnode != NULL)
		midisplaytree(root->rnode);
}


int main(){
	int i = 0;
	bnode* root = NULL;
	for(i=0;i<20;i++)
		insertobtree(&root, i, i+1);
	midisplaytree(root);
	printf("\b \n");

	destroybtree(root);
	printf("\n");
}

