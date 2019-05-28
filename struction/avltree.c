#include <stdio.h>
#include <stdlib.h>

#define HEIGHT(p) ( (p==NULL) ? 0 : (((anode*)(p))->height) )
#define MAX(a, b) ( (a)>(b) ? (a) : (b) )

typedef struct anode {
	int val;
	int height;
	struct anode *left, *right;
}anode;

anode* newanode(int val){
	anode* new = (anode*)malloc(sizeof(anode));
	new->val = val;
	new->height = 0;
	new->left = NULL;
	new->right = NULL;
	return new;
}
 
// LL
//              x
//             / \
//            y   c
//          /  \
//         a    b
//        /or\
//       d    e
anode* left_left_rotate(anode* x){
	anode* y = x->left;
	x->left = y->right;
	y->right = x;

	x->height = MAX(HEIGHT(x->right), HEIGHT(x->left)) + 1;
	y->height = MAX(HEIGHT(y->left), x->height) + 1;

	return y;
}

//RR
//              x
//             / \
//            a   y
//               /  \
//              b    c
//                  /or\
//                 e    d
anode* right_right_rotate(anode* x){
	anode *y = x->right;
	x->right = y->left;
	y->left = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), x->height) + 1;

	return y;
}

//LR
//             x
//            / \
//           y   a
//          / \
//        b    c
//            /or\
//           d    e
anode* left_right_rotate(anode* x){
	x->left = right_right_rotate(x->left);
	return left_left_rotate(x);
}

//RL
//             x
//            / \
//           a   y
//              / \
//             b   c
//            /or\
//           d    e
anode* right_left_rotate(anode* x){
	x->right = left_left_rotate(x->right);
	return right_right_rotate(x);
}




anode* avltree_insert(anode* root, int val){
	if(root == NULL){
		root = newanode(val);
	}else if(val < root->val){
		root->left = avltree_insert(root->left, val);
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2){
			if(val < root->left->val)
				root = left_left_rotate(root);
			else
				root = left_right_rotate(root);
		}
	}else if(val > root->val){
		root->right = avltree_insert(root->right, val);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2){
			if(val < root->right->val)
				root = right_left_rotate(root);
			else
				root = right_right_rotate(root);
		}
	}else{
		printf("same val in avl tree\n");
	}

	root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;

	return root;
}

anode* findmin(anode* root){
	if(root == NULL) return NULL;
	anode* min = root;
	while(min->left)
		min = min->left;
	return min;
}

anode* findmax(anode* root){
	if(root == NULL) return ;
	anode* max = root->right;
	while(max->right)
		max = max->right;
	return max;
}

anode* avltree_delete(anode* root, int val){
	if(root == NULL) return NULL;

	if(val < root->val){
		root->left = avltree_delete(root->left, val);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2){
			anode* r = root->right;
			if(HEIGHT(r->left) > HEIGHT(r->right)){
				root = right_left_rotate(root);
			}else{
				root = right_right_rotate(root);
			}
		}
	}else if(val > root->val){
		root->right = avltree_delete(root->right, val);
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2){
			anode* l = root->left;
			if(HEIGHT(l->left) > HEIGHT(l->right)){
				root = left_left_rotate(root);
			}else{
				root = left_right_rotate(root);
			}
		}
	}else{
		if(root->left && root->right){
			if(HEIGHT(root->left) > HEIGHT(root->left)){
				anode* max = findmax(root->left);
				root->val = max->val;
				root->left = avltree_delete(root->left, max->val);
			}else{
				anode* min = findmin(root->right);
				root->val = min->val;
				root->right = avltree_delete(root->right, min->val);
			}
		}else{
			anode* dnode = root;
			if(root->left)
				root = root->left;
			else
				root = root->right;
			free(dnode);
		}
	}
	return root;
}


void displaytree(anode* root){
	if(root == NULL) return ;
	displaytree(root->left);
	printf(".[%d|%d]", root->val, root->height);
	displaytree(root->right);
}

void destroytree(anode* root){
	if(root == NULL) return ;
	destroytree(root->left);
	destroytree(root->right);
	printf("-[%d|%d]", root->val, root->height);
	free(root);
}

void main(){
	int arr[16] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
	int i = 0;
	anode* tree = NULL;

	for(i=0; i<16; i++)
		tree = avltree_insert(tree, arr[i]);

	displaytree(tree);
	printf("\n");

	avltree_delete(tree, 8);

	displaytree(tree);
	printf("\n");
	destroytree(tree);
	printf("\n");
}








