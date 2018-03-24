#include <stdio.h>
#include <stdlib.h>

typedef struct treenode{
	int data;
	int height;
	struct treenode *lnode,*rnode;
}node;

node* initbtree(int i){
	node* root = (node*)malloc(sizeof(node));
	if(root==NULL){
		printf("init b tree fail\n");
		return NULL;
	}
	root->data=i;
	root->height=0;
	root->lnode=NULL;
	root->rnode=NULL;
	return root;
}

void insertree(node* root,int i,int height){
	if(root==NULL){
		printf("b tree need init\n");
		return ;
	}
	int h;
	node* tmp = (node*)malloc(sizeof(node));
	tmp->data=i;
	h=tmp->height=height+1;
	tmp->lnode=NULL;
	tmp->rnode=NULL;

	if(root->data>=i){
		(root->lnode==NULL)?(root->lnode=tmp):(free(tmp),insertree(root->lnode,i,h));
	}else{
		(root->rnode==NULL)?(root->rnode=tmp):(free(tmp),insertree(root->rnode,i,h));
	}

}



void midprintree(node* root){
	if(root==NULL){
		printf("b tree is empty\n");
		return ;
	}
	if(root->lnode!=NULL){
		midprintree(root->lnode);
	}
	if(root!=NULL){
		printf("data:%d\theight:%d\n",root->data,root->height);
	}
	if(root->rnode!=NULL){
		midprintree(root->rnode);
	}
}

int main(){
	node* root = initbtree(0);
	if(root==NULL){
		printf("init fail\n");
	}
	insertree(root,1,root->height);
	insertree(root,2,root->height);
	insertree(root,6,root->height);
	insertree(root,14,root->height);
	insertree(root,5,root->height);
	insertree(root,4,root->height);
	insertree(root,21,root->height);
	insertree(root,3,root->height);

	midprintree(root);


	
	return 0;
}
