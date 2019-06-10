#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct rbnode {
	int val;
	int color;
	struct rbnode* parent, *left, *right;
}rbnode;

typedef struct rbtree {
	struct rbnode* root;
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
	tree->root =  NULL;
	return tree;
}

//           x                 y
//              y           x     z
//                 z
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

//         x            y
//      y            z     x
//   z
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
	while((parent=new->parent) && (parent->color == RED)){
		gparent = parent->parent;
		if(gparent->left == parent){
			rbnode* uncle = gparent->right;
			if(uncle && uncle->color == RED){
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
				new = parent;
			}

			gparent->color = RED;
			parent->color = BLACK;
			rbtree_right_rotate(tree, gparent);
		}else{
			rbnode* uncle = gparent->left;
			if(uncle && uncle->color == RED){
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
			//         parent
			//   child.b   other.r
			if(other && other->color == RED){
				other->color = BLACK;
				parent->color = RED;
				rbtree_left_rotate(tree, parent);
				other = parent->right;
			}
			//       parent
			//  child.b   other.b
			//           o1.b   o2.b
			if((!(other->left) || (other->left->color == BLACK))
				&&(!(other->right)) || (other->right->color == BLACK)){
				otther->color = RED;
				child = parent;
				parent = child->parent;
			}else{
				//          parent
				//   child.r      other.b
				//             o1.r      o2.b
				if(!other->right || oother->right->color == BLACK){
					other->color = RED;
					other->left->color = BLACK;
					rbtree_right_rotate(tree, other);
					other = parent->right;
				}
				//          parent
				//   child.r       other.b
				//              o1.      o2 r
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				rbtree_left_rotate(tree, parent);
				new = tree->root;
				break;
			}
		}else{

		}
	}
}

void rbtree_delete_rbnode(rbtree* tree, rbnode* dnode){
	if(root == NULL) return ;

	rbnode *child, *parent;
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























void main(){

}
