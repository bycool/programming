#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct rbnode {
	int val;
	int color;
	struct rbnode *parent, *left, *right;
}rbnode;

typedef struct rbtree {
	struct rbnode *root;
}rbtree;

rbnode* newrbnode(int val){
	rbnode* new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->color = RED;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

rbtree* newrbtree(){
	rbtree* new = (rbtree*)malloc(sizeof(rbtree));
	new->root = NULL;
	return new;
}

/*          |
 *          x
 *         / \
 *        a   y
 *           / \
 *          b   c
 */
void rbtree_left_rotate(rbtree* tree, rbnode* x){
	rbnode* y = x->right;

	x->right = y->left;
	if(y->left)
		y->left->parent = x;

	y->parent = x->parent;
	if(x->parent == NULL){
		tree->root = y;
	}else{
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

/*         |
 *         y
 *        / \
 *       x   a
 *      / \
 *     b   c
 */
void rbtree_right_rotate(rbtree* tree, rbnode* y){
	rbnode* x = y->left;

	y->left = x->right;
	if(x->right)
		x->right->parent = y;

	x->parent = y->parent;
	if(x->parent == NULL){
		tree->root = x;
	}else{
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	x->right = y;
	y->parent = x;
}

void rbtree_insert_fixup(rbtree* tree, rbnode* new){
	rbnode *gparent, *parent;

	while((parent = new->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(gparent && (gparent->left == parent)){
			rbnode* uncle = gparent->right;
			if(uncle && (uncle->color == RED)){
				gparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				new = gparent;
				continue;
			}

			if(parent->right == new){
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
				gparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				new = gparent;;
				continue;
			}

			if(parent->left == new){
				rbnode* tmp;
				rbtree_right_rotate(tree, parent);
				tmp = parent;
				parent = new;
				new = tmp;
			}

			gparent->color = RED;
			parent->color = BLACK;
			rbtree_left_rotate(tree, gparent);
		}
	}
	tree->root->color = BLACK;
}

void rbtree_insert_rbnode(rbtree* tree, rbnode* new){
	if(tree == NULL) return ;
	rbnode* pn = NULL;
	rbnode* tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	new->parent = pn;
	if(pn == NULL){
		tree->root = new;
	}else{
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}

	new->color = RED;

	rbtree_insert_fixup(tree, new);
}

void lrd_displayrbnode(rbnode* root){
	if(root == NULL) return ;
	lrd_displayrbnode(root->left);
	lrd_displayrbnode(root->right);
	printf(".[%d|%d]", root->val, root->color);
}

void lrd_displaytree(rbtree* tree){
	if(tree == NULL) return ;
	lrd_displayrbnode(tree->root);
	printf("\n");
}

void destroyrbnode(rbnode* root){
	if(root == NULL) return ;
	destroyrbnode(root->left);
	destroyrbnode(root->right);
	printf("-[%d|%d]", root->val, root->color);
	free(root);
}

void destroyrbtree(rbtree* tree){
	if(tree == NULL) return ;
	destroyrbnode(tree->root);
	printf("-[tree]\n");
	free(tree);
}

void main(){
	rbtree* tree = NULL;
	rbnode* tmp = NULL;
	int i = 0;

	tree = newrbtree();
	for(i=0; i<10; i++){
		tmp = newrbnode(i);
		rbtree_insert_rbnode(tree, tmp);
	}

	lrd_displaytree(tree);

	destroyrbtree(tree);
}

