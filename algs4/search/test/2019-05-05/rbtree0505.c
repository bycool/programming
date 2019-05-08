#include <stdio.h>
#include <stdlib.h>

#define BLACK  0
#define RED    1

typedef struct rbnode {
	int val;
	int color;
	struct rbnode *parent,*left, *right;
}rbnode;

typedef struct rbtree {
	struct rbnode *root;
}rbtree;

rbnode* newrbnode(int val){
	rbnode *new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->color = RED;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void ldr_display(rbnode* root){
	if(root == NULL)  return ;
	ldr_display(root->left);
	printf(".[%d|%d]", root->val, root->color);
	ldr_display(root->right);
}

void ldr_displaytree(rbtree *tree){
	if(tree == NULL) return ;
	ldr_display(tree->root);
	printf("\n");
}

rbtree* creatree(){
	rbtree *tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

/*          |
 *          x
 *         / \
 *            y
 *           / \
 */
void rbtree_left_rotate(rbtree* tree, rbnode* x){
	rbnode *y = x->right;

	x->right = y->left;
	if(y->left)
		y->left->parent = x;

	y->parent = x->parent;
	if(x->parent){
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}else{
		tree->root = y;
	}

	y->left = x;
	x->parent = y;
}

/*         |
 *         y
 *        / \
 *       x
 *      / \
 */
void rbtree_right_rotate(rbtree* tree, rbnode* y){
	rbnode *x = y->left;

	y->left = x->right;
	if(x->right)
		x->right->parent = y;

	x->parent = y->parent;
	if(y->parent){
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;
	}else{
		tree->root = x;
	}

	x->right = y;
	y->parent = x;
}


void rbtree_insert_fixup(rbtree* tree, rbnode* new){
	rbnode *parent, *gparent;
	while((parent=new->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(parent == gparent->left){
			rbnode* uncle = gparent->right;
			if(uncle && (uncle->color == RED)){
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				new = gparent;
				continue;
			}

			if(new == parent->right){
				rbnode* tmp;
				rbtree_left_rotate(tree, parent);
				tmp = parent;
				parent = new;
				new = tmp;
			}

			gparent->color = RED;
			parent->color = BLACK;
			rbtree_right_rotate(tree, gparent);
		}else{
			rbnode* uncle = gparent->left;
			if(uncle && (uncle->color == RED)){
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				new = gparent;
				continue;
			}

			if(new == parent->left){
				rbnode* tmp;
				rbtree_right_rotate(tree, parent);
				tmp = parent;
				parent = new;
				new = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_left_rotate(tree, gparent);
		}
	}
	tree->root->color = BLACK;
}


void rbtree_insert_rbnode(rbtree* tree, rbnode* new){
	rbnode* np = NULL;
	rbnode* tmp = tree->root;

	while(tmp){
		np = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	new->parent = np;
	if(np){
		if(new->val < np->val)
			np->left = new;
		else
			np->right = new;
	}else{
		tree->root = new;
	}
	new->color = RED;

	rbtree_insert_fixup(tree, new);
	ldr_displaytree(tree);
}


void destroynode(rbnode *root){
	if(root == NULL) return ;
	destroynode(root->left);
	destroynode(root->right);
	printf("-[%d|%d]", root->val, root->color);
	free(root);
}

void destroytree(rbtree* tree){
	if(tree == NULL) return ;
	destroynode(tree->root);
	printf("-[tree]\n");
	free(tree);
}


void main(){
	int i = 0;
	rbtree* tree = NULL;
	rbnode* tmp = NULL;

	tree = creatree();
	for(i=0; i<10; i++){
		tmp = newrbnode(i);
		rbtree_insert_rbnode(tree, tmp);
	}

	ldr_displaytree(tree);
	destroytree(tree);
}

