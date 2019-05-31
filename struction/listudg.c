#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define LENGTH(p) ( (sizeof(p))/(sizeof(p[0])) )

typedef struct enode {
	int v;
	struct enode* next;
}enode;

typedef struct vnode {
	char v;
	struct enode* next;
}vnode;

typedef struct Graph {
	int vexnum;
	int edgnum;
	vnode vexs[MAX];
}Graph;


int getxy(Graph* g, char c){
	int i = 0;
	for(i=0; i<g->vexnum; i++)
		if(g->vexs[i].v == c)
			return i;
	return -1;
}

Graph* create_graph(){

	int i = 0;
	char x, y;
	enode* new = NULL;
	enode* p = NULL;

	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edgs[][2] = {
        {'A','C'},
        {'A','D'},
        {'A','F'},
        {'B','C'},
        {'C','D'},
        {'E','G'},
        {'F','G'}};

	int vlen = LENGTH(vexs);
	int elen = LENGTH(edgs);

	Graph* g = (Graph*)malloc(sizeof(Graph));
	memset(g, 0x0, sizeof(Graph));

	g->vexnum = vlen;
	g->edgnum = elen;

	for(i=0; i<g->vexnum; i++){
		g->vexs[i].v = vexs[i];
		g->vexs[i].next = NULL;
	}

	for(i=0; i<g->edgnum; i++){
		x = edgs[i][0];
		y = edgs[i][1];

		new = (enode*)malloc(sizeof(enode));
		new->v = y;
		new->next = NULL;

		p = g->vexs[x].next;
		if(p == NULL){
			g->vexs[x].next = new;
		}else{
			while(p->next)
				p = p->next;
			p->next = new;
		}
	}
	return g;
}

void print_vnodelist(vnode* vn){
	
}


void print_graph(Graph* g){
	int i = 0;

	for(i=0; i<g->vexnum; i++)
		printf(" [%c] ", g->vexs[i]);
	printf("\n");

	
}


void main(){
	Graph* g = create_graph();
	print_graph(g);
	free(g);
}

