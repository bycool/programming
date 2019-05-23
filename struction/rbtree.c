#include <stdio.h>
#include <stdlib.h>

#define RED   0
#define BLACK 1

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
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return new;
}

rbtree* newrbtree(){
	rbtree* tree = (rbtree*)malloc(sizeof(rbtree));
	tree->root = NULL;
	return tree;
}

/*            |
 *            x
 *           / \
 *          a   y
 *             / \
 *            b   c
 */
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

/*       |
 *       y
 *      / \
 *     x   a
 *    / \
 *   b   c
 */
void rbtree_right_rotate(rbtree* tree, rbnode* y){
	rbnode* x = y->left;

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
			if((uncle) && (uncle->color == RED)){
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

			parent->color = BLACK;
			gparent->color = RED;
			rbtree_right_rotate(tree, gparent);
		}else{
			rbnode *uncle = gparent->left;
			if((uncle) && (uncle->color == RED)){
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
	if(tree == NULL) return ;

	rbnode* tmp = tree->root;
	rbnode* pn = NULL;
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

void rbtree_delete_fixup(rbtree* tree, rbnode* child, rbnode* parent){
	rbnode* other;

	while((!child || child->color == BLACK) && tree->root != child){
		if(child == parent->left){
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
				//          other.b
				//    left.r      right.b
				//
				if(!other->right || other->right->color == BLACK){
					other->left->color = BLACK;
					other->color = RED;
					rbtree_right_rotate(tree, other);
					other = parent->right;
				}

				//          other.r
				//    left        right.r
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				rbtree_left_rotate(tree, parent);
				child = tree->root;
				break;
			}
		}else{
			other = parent->left;
			if(other->color == RED){
				other->color = BLACK;
				parent->color = RED;
				rbtree_right_rotate(tree, other);
				other = parent->right;
			}

			if((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK)){
				other->color = RED;
				child = parent;
				parent = child->parent;
			}else{
				if(!other->left || other->left->color == BLACK){
					other->right->color = BLACK;
					other->color = RED;
					rbtree_left_rotate(tree, other);
					other = parent->left;
				}
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rbtree_right_rotate(tree, parent);
				child = tree->root;
				break;
			}
			
		}
	}
	if(child)
		child->color = BLACK;
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

			if( (!other->left || other->left->color == BLACK) &&
				(!other->right || other->right->color == BLACK)){
				other->color = BLACK;
				child = parent;
				parent = parent->parent;
			}eles{
				if(!other->right || other->right->color == BLACK){
					other->left->color = BLACK;
					other->color = RED;
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
	rbnode *child, *parnet;
	int color;

	if(dnode->left && dnode->right){
		rbnode* replace = dnode->right;
		while(replace->left)
			replace = replace->left;

		child = replace->right;
		parent = replace->parent;
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
		replace->color = dnode->color;
		replace->left->parent = replace;
		replace->parent = dnode->parent;

		if(color == BLACK)
			rbtree_delete_fixup(tree, child, parent);

		free(dnode);
		return ;
	}

	if(dnode->left)
		child = dnode->left;
	else
		child = dnode->right;
	child->parent = parent;

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



void ldr_displayrbnode(rbnode* root){
	if(root == NULL) return ;
	ldr_displayrbnode(root->left);
	printf(".[%d]", root->val);
	ldr_displayrbnode(root->right);
}

void ldr_displaytree(rbtree* tree){
	if(tree == NULL) return ;
	ldr_displayrbnode(tree->root);
	printf("\n");
}

void destroyrbnode(rbnode* root){
	if(root == NULL) return ;
	destroyrbnode(root->left);
	destroyrbnode(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destroytree(rbtree* tree){
	if(tree == NULL) return ;
	destroyrbnode(tree->root);
}

void main(){
	int i = 0;
	rbtree* tree = newrbtree();
	rbnode* tmp = NULL;
	for(i=0; i<10; i++){
		tmp = newrbnode(i);
		rbtree_insert_rbnode(tree, tmp);
	}

	ldr_displaytree(tree);

	destroytree(tree);

}
