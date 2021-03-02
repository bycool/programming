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

void rbtree_delete_fixup(rbtree* tree, rbnode* child, rbnode* parent){
	rbnode *other;

	while((!child || child->color == BLACK) && tree->root != child){
		if(parent->left == child){
			other = parent->right;
			if(other->color == RED){
				other->color = BLACK;
				parent->color = RED;
				rbtree_left_rotate(tree, parent);
				other = parent->right;
			}

			if((!other->left || other->left->color == BLACK) &&
				(!other->right || other->right->color == BLACK)){
				other->color = RED;
				child = parent;
				parent = child->parent;
			}else{
				//        other
				//   left.r   right.b
				if(!other->right || other->right->color == BLACK){
					other->color = RED;
					other->left->color = BLACK;
					rbtree_right_rotate(tree, other);
					other = parent->right;
				}
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				rbtree_left_rotate(tree, parent);
				child = tree->root;
				break;
			}
		}else{

		}
	}
	if(child)
		child->color = BLACK;
}

void rbtree_delete_rbnode(rbtree* tree, rbnode* dnode){
	rbnode *parent, *child;
	int color;

	if(dnode->left && dnode->right){
		rbnode *replace = dnode->right;
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
		replace->parent = dnode->parent;
		replace->color = dnode->color;

		if(color == BLACK)
			rbtree_delete_fixup(tree, child, parent);

		free(dnode);
		return ;
	}

	if(dnode->left)
		child = dnode->left;
	else
		child = dnode->right;

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


rbtree* create_tree(){
	rbtree *tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

void lrd_displaynodes(rbnode* root){
	if(root==NULL) return;
	lrd_displaynodes(root->left);
	printf(".[%d]", root->val);
	lrd_displaynodes(root->right);
}

void lrd_display(rbtree* tree){
	if(tree == NULL) return;
	lrd_displaynodes(tree->root);
	printf("\n");
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
	free(tree);
	printf("-[tree]\n");
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

	destroytree(tree);
}


