#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BALCK 1

typedef struct rbnode {
	int val;
	int color;
	struct rbnode *parent, *left, *right;
}rbnode;

typedef struct rbtree {
	rbnode *root;
}rbtree;

rbnode* newrbnode(int val){
	rbnode* new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->color = RED;
	new->parent = new->left = new->right = NULL;
	return new;
}

rbtree* create_tree(){
	rbtree* tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

//         x
//       /   \
//      a      y
//           /   \
//         b       z
//               /   \
//
void rbtree_left_rotate(rbtree* tree, rbnode* x){
	rbtree* y = x->right;

	x->right = y->left;
	if(y->left)
		y->left->parent = x;

	y->parent = x->parent;
	if(x->parent){
		if(x->parent->left == x)
			x->paret->left = y;
		else
			x->parent->right = y;
	}else{
		tree->root = y;
	}

	y->left = x;
	x->parent = y;
}

//               x
//             /   \
//           y      a
//         /   \
//        b      c
void rbtree_right_rotate(rbtree* tree, rbnode* x){
	rbnode* y = x->left;

	x->left = y->right;
	if(y->right)
		y->right->parent = x;

	y->parent = x->parent;
	if(x->parent){
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}else{
		tree->root = y;
	}

	y->right = x;
	x->parent = y;
}

void rbtree_insert_fixup(rbtree* tree, rbnode* new){
	rbnode *parent, *gparent;

	while((parent=new->parent) && parent->color == RED){
		gparent = parent->parent;
		if(parent == gparent->left){
			rbnode* uncle = gparent->right;
			if(uncle && uncle->color == RED){
				uncle->color = BLACK;
				parent->color = BLACK;
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
			if(uncle && uncle->color == RED){
				uncle->color = BLACK;
				parent->color = BLACK;
				gprent->color = RED;
				new = gparent;
				continue;
			}

			if(new == parent->left){
				rbnode* tmp;
				rbnode_right_rotate(tree, parent);
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

	if(pn){
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}else{
		tree->root = new;
	}

	new->color = RED;

	rbtree_insert_fixup(tree, new);
}







