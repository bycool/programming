#include <stdio.h>
#include <stdlib.h>

#define HEIGHT(p) ( ((p) == NULL) ? 0 : ((node*)(p))->height )
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

typedef struct node {
	int val;
	int height;
	struct node *left, *right;
}node;

node* newnode(int val){
	node* new = (node*)malloc(sizeof(node));
	new->val = val;
	new->height = 0;
	new->left = NULL;
	new->left = NULL;
	return new;
}

//LL
//              x
//           y
//        z
//      1  1
node* left_left_rotate(node* x){
	node* y = x->left;
	x->left = y->right;
	y->right = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), HEIGHT(y->right)) + 1;

	return y;
}

//RR
//              x
//                 y
//                    z
//                   1 1
node* right_right_rotate(node* x){
	node* y = x->right;
	x->right = y->left;
	y->left = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), HEIGHT(x->right)) + 1;

	return y;
}

//LR
//            x
//        y
//          z
//         1 1
node* left_right_rotate(node* x){
	x->left = right_right_rotate(x->left);
	return left_left_rotate(x);
}

//RL
//           x
//               y
//            z
//           1 1
node* right_left_rotate(node* x){
	x->right = left_left_rotate(x->right);
	return right_right_rotate(x);
}


//insert
node* avltree_insert(node* root, int val){
	if(root == NULL){
		root = newnode(val);
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
		printf("same val in avltree, cant insert %d to tree\n", val);
	}

	root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;

	return root;
}

node* findmin(node* root){
	if(root == NULL) return NULL;
	node* min = root;
	while(min->left)
		min = min->left;
	return min;
}

node* findmax(node* root){
	if(root == NULL) return NULL;
	node* max = root;
	while(max->right)
		max = max->right;
	return max;
}

node* avltree_delete(node* root, int val){
	if(root == NULL) return NULL;

	if(val < root->val){
		root->left = avltree_delete(root->left, val);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2){
			node* r = root->right;
			if(HEIGHT(r->left) > HEIGHT(r->right))
				root = right_left_rotate(root);
			else
				root = right_right_rotate(root);
		}
	}else if(val > root->val){
		root->right = avltree_delete(root->right, val);
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2){
			node* l = root->left;
			if(HEIGHT(l->left) > HEIGHT(l->right))
				root = left_left_rotate(root);
			else
				root = left_right_rotate(root);
		}
	}else{
		if(root->left && root->right){
			if(HEIGHT(root->left) > HEIGHT(root->right)){
				node* max = findmax(root->left);
				root->val = max->val;
				root->left = avltree_delete(root->left, max->val);
			}else{
				node* min = findmin(root->right);
				root->val = min->val;
				root->right = avltree_delete(root->right, min->val);
			}
		}else{
			node* dnode = root;
			if(root->left)
				root = root->left;
			else
				root = root->right;
			free(dnode);			
		}
	}
	return root;
}

void displaytree(node* root){
	if(root == NULL) return ;
	displaytree(root->left);
	printf(".[%d|%d]", root->val, root->height);
	displaytree(root->right);
}

void destorytree(node* root){
	if(root == NULL) return ;
	destorytree(root->left);
	destorytree(root->right);
	printf("-[%d|%d]", root->val, root->height);
}


void main(){
    int arr[16] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    int i = 0;
    node* tree = NULL;

    for(i=0; i<16; i++)
        tree = avltree_insert(tree, arr[i]);

    displaytree(tree);
    printf("\n");

    avltree_delete(tree, 8);

    displaytree(tree);
    printf("\n");
    destorytree(tree);
    printf("\n");

}
