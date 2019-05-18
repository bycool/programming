#include <stdio.h>
#include <stdlib.h>

#define     RED	    1
#define     BLACK   0

typedef struct rbnode {
	struct rbnode *parent;
	int val;
	int color;
	struct rbnode *left, *right;
}rbnode;

typedef struct rbtree {
	struct rbnode *root;
}rbtree;

/*      |    left rotate
 *      x
 *    /   \
 *   a     y
 *        / \
 *       b   c
 */      
void rbtree_left_rotate(rbtree *tree, rbnode *x){
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

/*        |   right rotate
 *	      y
 *	    /   \
 *     x     c
 *    / \
 *   a   b
 */
void rbtree_right_rotate(rbtree *tree, rbnode *y){
	rbnode *x = y->left;

	y->left = x->right;
	if(x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if(y->parent == NULL){
		tree->root = y;
	}else{
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
}



rbnode *new_rbnode(int val){
	rbnode *new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->color = RED;
	return new;
}

void rbtree_insert_fixup(rbtree *tree, rbnode *node){
	rbnode *parent, *gparent;

	while((parent = node->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(parent == gparent->left)
		{
			{
				rbnode *uncle = gparent->right;
				if(uncle && (uncle->color == RED)){
					parent->color = BLACK;
					uncle->color = BLACK;
					gparent->color = RED;
					node = gparent;
					continue;
				}
			}

			if(node == parent->right){
				rbnode *tmp;
				rbtree_left_rotate(tree, parent);
				tmp = parent;
				parent = node;;
				node = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_right_rotate(tree, gparent);
		}
		else
		{
			{
				rbnode *uncle = gparent->left;
				if(uncle && (uncle->color == RED)){
					parent->color = BLACK;
					uncle->color = BLACK;
					gparent->color = RED;
					node = gparent;
					continue;
				}
			}

			if(node == parent->left){
				rbnode *tmp;
				rbtree_right_rotate(tree, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_left_rotate(tree, gparent);
			
		}
	}
	tree->root->color = BLACK;
}

/* 
 * insert nodes to tree
 */
void rbtree_insert_rbnode(rbtree *tree, rbnode *new){
	rbnode *parent = NULL;
	rbnode *tmp = tree->root;

	while(tmp){
		parent = tmp;
		if(new->val < parent->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	new->parent = parent;

	if(parent != NULL){
		if(new->val < parent->val)
			parent->left = new;
		else
			parent->right = new;
	}else{
		tree->root = new;
	}

	new->color = RED;

	rbtree_insert_fixup(tree, new);
}

void rbtree_delete_fixup(rbtree *tree, rbnode* dnode, rbnode* parent){

}

void rbtree_delete_rbnode(rbtree *tree, rbnode *dnode){
	
}














void rbtree_delete_rbnode(rbtree *tree, rbnode *dnode){
	rbnode *child, *parent;
	int color;

	if(dnode->left && dnode->right){
		rbnode *replace = dnode->right;
		while(replace->left)
			replace = replace->left;

		if(dnode->parent){
			if(dnode->parent->left == dnode)
				dnode->parent->left = replace;
			else
				dnode->parent->right = replace;
		}else{
			tree->root = replace;
		}

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if(parent == dnode){
			parent = replace;
		}else{
			if(child)
				child->parent = parent;
			parent->left = child;

			replace->right = dnode->right;
			dnode->right->parent = replace;
		}

		replace->left = dnode->left;
		dnode->left->parent = replace;
		replace->parent = dnode->parent;
		replace->color = dnode->color;

		if(color == BLACK)
			rebtree_delete_fixup(tree, child, parent);

		free(dnode);
		return ;
	}

	if(dnode->left != NULL)
		child = dnode->left;
	else
		child = dnode->right;
	child->parent = dnode->parent;

	parent = dnode->parent;
	color = dnode->color;


	if(parent){
		if(parent->left == dnode)
			parent->left = child;
		else
			parent->right = child;
	}else{
		tree->root = child;
	}

	if(color == BLACK)
		rbtree_delete_fixup(tree, child, parent);

	free(dnode);
}


void lrd_display(rbnode *root){
	if(root == NULL) return ;
	lrd_display(root->left);
	lrd_display(root->right);
	printf(".[%d]", root->val);
}

void lrd_displaytree(rbtree *tree){
	if(tree != NULL)
		lrd_display(tree->root);
}

void destroynode(rbnode *root){
	if(root == NULL) return ;
	destroynode(root->left);
	destroynode(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destroytree(rbtree *tree){
	if(tree->root != NULL)
		destroynode(tree->root);
	free(tree);
}

rbtree *create_tree(){
	rbtree *tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

void main(){
	int i = 0;
	rbtree *tree = create_tree();
	rbnode *new = NULL;
	for(i=0; i<10; i++){
		new = new_rbnode(i);
		rbtree_insert_rbnode(tree, new);
	}

	lrd_displaytree(tree);
	printf("\n");

	destroytree(tree);
	printf("\n");
}



