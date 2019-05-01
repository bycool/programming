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
	rbnode *root;
}rbtree;

/*        |
 *        x
 *      /   \
 *     a     y
 *          / \
 *         b   c
 */        
void rbtree_left_rotate(rbtree* tree, rbnode* x){
	rbnode *y = x->right;

	x->right = y->left;
	if(y->left != NULL)
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

/*       |
 *       y
 *     /   \
 *    x     c
 *   / \
 *  a   b
 */
void rbtree_right_rotate(rbtree* tree, rbnode* y){
	rbnode *x = y->left;

	y->left = x->right;
	if(x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if(y->parent == NULL){
		tree->root = x;
	}else{
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = y;
	}

	x->right = y;
	y->parent = x;
}

rbnode* newrbnode(int val){
	rbnode* new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->color = RED;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void rbtree_insert_fixup(rbtree* tree, rbnode* new){
	rbnode *parent, *gparent;
	while((parent=new->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(gparent->left == parent){
			rbnode* uncle = gparent->right;
			if(uncle && (uncle->color == RED)){
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
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

			parent->color = BLACK;
			gparent->color = RED;
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

			if(parent->left == new){
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

void rbtree_insert_node(rbtree* tree, rbnode* new){
	rbnode* tmp = tree->root;
	rbnode* ptmp = NULL;

	while(tmp != NULL){
		ptmp = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	new->parent = ptmp;

	if(new->parent == NULL){
		tree->root = new;
	}else{
		if(new->val < ptmp->val)
			ptmp->left = new;
		else
			ptmp->right = new;
	}

	new->color = RED;

	rbtree_insert_fixup(tree, new);
}

rbtree* create_tree(){
	rbtree *tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

void lrd_displaynodes(rbnode* root){
	if(root==NULL) return;
	lrd_displaynodes(root->left);
	lrd_displaynodes(root->right);
	printf(".[%d]", root->val);
}

void lrd_display(rbtree* tree){
	if(tree == NULL) return;
	lrd_displaynodes(tree->root);
}

void destroynodes(rbnode* root){
	if(root==NULL) return;
	destroynodes(root->left);
	destroynodes(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destroytree(rbtree *tree){
	if(tree == NULL) return;
	destroynodes(tree->root);
}


void main(){
	int i = 0;
	rbnode* new = NULL;
	rbtree* tree = create_tree();
	
	for(i=0; i<10; i++){
		new = newrbnode(i);
		rbtree_insert_node(tree, new);
	}

	lrd_display(tree);
	printf("\n");

	destroytree(tree);
	printf("\n");
}


