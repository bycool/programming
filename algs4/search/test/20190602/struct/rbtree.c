#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct rbnode {
	int val;
	int color;
	struct rbnode *parent, *left, *right;
}rbnode;

typedef struct rbtree {
	rbnode* root;
}rbtree;


rbnode* newrbnode(int val){
	rbnode* new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->color = BLACK;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

rbtree* newrbtree(){
	rbtree* tree = (rbnode*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

//                x
//            a        y
//                   c   d
void rbtree_left_rotate(rbtree* tree, rbnode* x){
	rbnode* y = x->right;

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

//                  x
//           y           a
//         b   c
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
	rbnode* gparent, *parent;

	while((parent=new->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(parent == gparent->left){
			rbnode* uncle = gparent->right;
			if((uncle) && uncle->color == RED){
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
			if((uncle) && uncle->color == RED){
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

			gparent->color = RED;
			parent->color = BLACK;
			rbtree_left_rotate(tree, gparent);
		}
	}
	tree->root->color = BLACK;
}

void rbtree_insert_rbnode(rbtree* tree, rbnode* new){
	if(tree == NULL) return NULL;

	rbnode* pn = NULL;
	rbnode* tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->rigt;
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

void rbtree_delete_fixup(rbtree* tree, rbnode* child, rbnode* parent){
	rbnode* other;
	while(((!child) || (child->color == BLACK))  && tree->root != child){
		if(parent->left == child){
			other = parent->right;
			if(!other || other->color == RED){
				other->color = BLACK;
				parent->color = RED;
				rbtree_left_rotate(tree, parent);
				other = parent->right;
			}

			if((!(other->left) || other->left->color == BLACK) &&
				(!(other->right) || other->right->color = BLACK)){
				other->color = RED;
				child = parent;
				parent = child->parent;
			}else{
				if(
			}
		else{

		}
	}
}

void rbtree_delete_rbnode(rbtree* tree, rbnode* dnode){
	rbnode *parent, *child;
	int color;

	if(dnode->left && dnode->right){
		rbnode* replace = dnode->right;
		while(replace->left)
			replace = replace->left;

		parent = replace->parent;
		child = replace->right;
		color = replace->color;

		if(dnode->parent){
			if(dnode->parent->left == dnode)
				dnode->parent->left = replace;
			else
				dnode->parent->right = replace;
		}else{
			tree->root = replace;
		}

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
		replace->color = dnode->color;
		replace->parent = dnode->parent;

		if(color == BLACK)
			rbtree_delete_fixup(tree, child, parent);

		free(dnode);
		return ;
	}

	if(dnode->left)
		child = dnode->right;
	else
		child = dnode->left;

	parent = dnode->parent;
	color = dnode->color;

	if(dnode->parent){
		if(dnode->parent->left == dnode)
			dnode->parent->left = child;
		else
			dnode->parent->right = child;
	}else{
		tree->root = child;
	}

	if(color == BLACK)
		rbtree_delete_fixup(tree, child, parent);
	free(dnode);
}






















