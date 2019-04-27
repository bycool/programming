#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0


typedef struct node {
	int val;
	int color;
	struct node *parent, *left, *right;
}node;

typedef struct Troot {
	node *root;
}Troot;

void rbtree_insert_fixup(Troot *root, node* node);

/*
    z 	                         z
    ||                           ||
    x                            y
 //   \\      对x进行左旋转   //   \\
a      y                      x     c
    //   \\                 // \\
   b       c               a     b

*/
void left_rotate(Troot *root, node* x){
	node* y = x->right;

	x->right = y->left;

	if(y->left != NULL)
		y->left->parent = x;  //先把y的左儿子b过给x,让x认b当儿子，在让b认x当爹。

	y->parent = x->parent; 

	if(x->parent == NULL){
		root->root = y;
	}else{
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}



/*
          z                        z
          ||                       ||
          y                        x
       //   \\   对y进行右旋    //   \\
      x      c                 a       y
    // \\                           //   \\
   a     b                         b       c

*/
void right_rotate(Troot *root, node* y){
	node* x = y->left;

	y->left = x->right;
	if(x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if(y->parent == NULL){
		root->root = x;
	}else{
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	x->right = y;
	y->parent = x;
}



/*
 *
 */
void rbtree_insert(Troot *root, node* new){
	node* y = NULL;
	node* x = root->root;

	while(x != NULL){
		y = x;
		if(new->val < x->val)
			x = x->left;
		else
			x = x->right;
	}
	new->parent = y;

	if(y != NULL){
		if(new->val < y->val)
			y->left = new;
		else
			y->right = new;
	}else{
		root->root = new;
	}
	new->color = RED;

	rbtree_insert_fixup(root, new);
}

void rbtree_insert_fixup(Troot *root, node* n){
	node *parent, *gparent;

	while((parent = n->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(parent == gparent->left){
			// case1:
			{
				node* uncle = gparent->right;
				if(uncle && (uncle->color == RED)){
					uncle->color = BLACK;
					parent->color = BLACK;
					gparent->color = RED;
					n = gparent;
					continue;
				}
			}

			// case2:
			if(parent->right == n){
				node* tmp ;
				left_rotate(root, parent);
				tmp = parent;
				parent = n;
				n = tmp;
			}

			// case3:
			parent->color = BLACK;
			gparent->color = RED;
			right_rotate(root, gparent);
		}else{
			{
				node* uncle = gparent->left;
				if(uncle && (uncle->color == RED)){
					uncle->color = BLACK;
					parent->color = BLACK;
					gparent->color = RED;
					n = gparent;
					continue;
				}
			}

			if(parent->left == n){
				node* tmp;
				right_rotate(root, parent);
				tmp = parent;
				parent = n;
				n = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			left_rotate(root, gparent);
		}
	}
	root->root->color = BLACK;
}

Troot* create_tree(){
	Troot* root = (Troot*)malloc(sizeof(Troot));
	root->root = NULL;
	return root;
}

node* newnode(int val){
	node* new = (node*)malloc(sizeof(node));
	new->val = val;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void midisplay(node* root){
	if(root == NULL) return ;
	midisplay(root->left);
/*	if(root->color == RED)
		printf("[%d|R]", root->val);
	else
		printf("[%d|B]", root->val);
*/
	midisplay(root->right);
	printf(".[%d]", root->val);
}

void midisplaytree(Troot* root){
	if(root == NULL) return ;
	midisplay(root->root);
}

void destroynodes(node *root){
	if(root == NULL) return ;
	destroynodes(root->left);
	destroynodes(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destroytree(Troot* root){
	if(root == NULL) return ;
	destroynodes(root->root);
}



void main(){
	Troot* tree = create_tree();
	node* tmp = NULL;
	int i = 0;
	for(i=0; i<10; i++){
		tmp = newnode(i);
		rbtree_insert(tree, tmp);
	}

	midisplaytree(tree);
	printf("\n");

	destroytree(tree);
	printf("\n");

}
