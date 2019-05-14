#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct rbnode {
	int val;
	int color;
	struct rbnode *left, *right, *parent;
}rbnode;

typedef struct rbtree {
	rbnode *root;
}rbtree;

rbnode *newrbnode(int val){
	rbnode* new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->color = RED;
	new->parent = NULL;
	new->left = NULL;
	new->righ = NULL;
	return new;
}

rbtree *newrbtree(){
	rbtree* tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

/*         |
 *         x
 *        / \
 *       a   y
 *          / \
 *         b   c
 */      
void rbtree_left_rotate(rbtree *tree, rbnode *x){
	rbnode *y = x->right;

	x->right = y->left;
	if(y->left)
		y->left->parent = x;

	y->parent = x->parent;
	if(y->parent){
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

/*        |
 *        y
 *       / \
 *      x   a
 *     / \
 *    b   c
 *
 */
void rbtree_right_rotate(rbtree *tree, rbnode *y){
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

void rbtree_insert_fixup(rbtree *tree, rbnode *new){
	if(tree == NULL) return ;

	rbnode *gparent, *parent;
	while((parent = new->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if( gparent && (parent == gparent->left) ){
			rbnode *uncle = gparent->right;
			if(uncle && (uncle->color == RED)){
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				new = gparent;
				continue;
			}

			if(new == parent->right){
				rbnode *tmp;
				rbtree_left_rotate(tree, parent);
				tmp = parent;
				parent = new;
				new = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_right_rotate(tree, gparent);
		}else{
			rbnode *uncle = gparent->left;
			if(uncle && (uncle->color == RED)){
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				new = gparent;
				continue;
			}

			if(new == parent->left){
				rbnode *tmp;
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

void rbtree_insert_rbnode(rbtree *tree, rbnode *new){
	if(tree == NULL) return ;

	rbnode *pn = NULL;
	rbnode *tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	new->parent = pn;

	if(pn){
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}else{
		tree->root = new;
	}

	new->color = RED;

	rbtree_insert_rbnode(tree, new);	

}


