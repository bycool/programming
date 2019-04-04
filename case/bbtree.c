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

void insertobtree(bnode *root, int key, int val){
	if(*root == NULL){
		*root = newnode(key, val);
		return;
	}

	bnode* nnode = (bnode*)malloc(sizeof(bnode));
	nnode->key = key;
	nnode->val = val;
	nnode->lnode = NULL;
	nnode->rnode = NULL;

	if(root->key > key){
		if(root->lnode == NULL){
			root->lnode = nnode;
		}else{
			free(nnode);
			insertobtree(root->lnode, key, val);
		}
	}else{
		if(root->rnode == NULL){
			root->rnode = nnode;
		}else{
			free(nnode);
			insertobtree(root->rnode, key, val);
		}
	}
}



int main(){

}

