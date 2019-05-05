#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct rbnode {
	struct rbnode *parent;
	int val;
	int color;
	struct rbnode *left, *right;
}rbnode;

typedef struct rbtree {
	struct rbnode* root;
}rbtree;

void lrd_display(rbnode* root){
	if(root == NULL) return;
	lrd_display(root->left);
	lrd_display(root->right);
	printf(".[%d]", root->val);
}

void lrd_displaytree(rbtree* tree){
	if(tree == NULL) return ;
	lrd_display(tree->root);
}

rbnode *newrbnode(int val){
	rbnode *new = (rbnode*)malloc(sizeof(rbnode));
	new->val = val;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

/*		|             |
 *		x             y
 *	     \          /
 *	      y       x
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
		if(x->parent->left == x){
			x->parent->left = y;
		}else{
			x->parent->right = y;
		}
	}

	y->left = x;
	x->parent = y;
}

/*       |             |
 *       y             x
 *     /                 \
 *   x                    y
 */
void rbtree_right_rotate(rbtree *tree, rbnode *y){
	rbnode *x = y->left;

	y->left = x->right;
	if(x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if(y->parent == NULL){
		tree->root = x;
	}else{
		if(y->parent->left == y){
			y->parent->left = x;
		}else{
			y->parent->right = y;
		}
	}

	x->right = y;
	y->parent = x;
}




void rbtree_insert_fixup(rbtree *tree, rbnode* n){
	rbnode *parent, *gparent;

	while((parent = n->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(parent == gparent->left){
			rbnode *uncle = gparent->right;
			if(uncle && (uncle->color == RED)){
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				n = gparent;
				continue;
			}

			if(n == parent->right){
				rbnode* tmp;
				rbtree_left_rotate(tree, parent);
				tmp = parent;
				parent = n;
				n = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_right_rotate(tree, gparent);
		}else{
			rbnode *uncle = gparent->left;
			if(uncle && (uncle->color == RED)){
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				n = gparent;
				continue;
			}

			if(n == parent->left){
				rbnode *tmp;
				rbtree_right_rotate(tree, parent);
				tmp = parent;
				parent = n;
				n = tmp;
			}

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_left_rotate(tree, gparent);
		}
	}
	tree->root->color = BLACK;
}


void rbtree_insert_node(rbtree *tree, rbnode* n){
	rbnode *tmp = tree->root;
	rbnode *p = NULL;

	while(tmp){
		p = tmp;
		if(n->val < tmp->val){
			tmp = tmp->left;
		}else{
			tmp = tmp->right;
		}
	}

	n->parent = p;
	if(n->parent == NULL){
		tree->root = n;
	}else{
		if(n->val < p->val){
			p->left = n;
		}else{
			p->right = n;
		}
	}
	n->color = RED;

	rbtree_insert_fixup(tree, n);
	//lrd_displaytree(tree);
}

void rbtree_insertree(rbtree *tree, int val){
	rbnode* new = newrbnode(val);
	if(tree != NULL)
		rbtree_insert_node(tree, new);
}

rbtree *create_tree(){
	rbtree *tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
}


void destroynode(rbnode* root){
	if(root == NULL) return ;
	destroynode(root->left);
	destroynode(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destroytree(rbtree* tree){
	if(tree == NULL) return ;
	destroynode(tree->root);
}

void main(){
	rbtree *tree = NULL;
	int i = 0;

	tree = create_tree();
	for(i=0; i<10; i++)
		rbtree_insertree(tree, i);

	lrd_displaytree(tree);
	printf("\n");

	destroytree(tree);
	printf("\n");
}









