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
	int a, b;
	enode* new = NULL;
	enode* new2 = NULL;
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

		a = getxy(g, x);
		b = getxy(g, y);

		printf("a: %d, b: %d\n", a, b);

		new = (enode*)malloc(sizeof(enode));
		new->v = b;
		new->next = NULL;

		p = g->vexs[a].next;
		if(p == NULL){
			g->vexs[a].next = new;
		}else{
			while(p->next)
				p = p->next;
			p->next = new;
		}

		new2 = (enode*)malloc(sizeof(enode));
		new2->v = a;
		new2->next = NULL;

		p = g->vexs[b].next;
		if(p == NULL){
			g->vexs[b].next = new2;
		}else{
			while(p->next)
				p = p->next;
			p->next = new2;
		}
	}
	return g;
}

void DFS(Graph* g, int c, int *visited){
	enode* p = NULL;

	visited[c] = 1;
	printf(" -> [%c]", g->vexs[c].v);

	p = g->vexs[c].next;
	while(p){
		if(!visited[p->v])
			DFS(g, p->v, visited);
		p = p->next;
	}
}

void DFStraverse(Graph* g){
	int i = 0;
	int visited[MAX];

	for(i=0; i<g->vexnum; i++)
		visited[i] = 0;

	printf("DFS: ");
	for(i=0; i<g->vexnum; i++){
		if(!visited[i])
			DFS(g, i, visited);
	}
	printf("\n");
}

void BFS(Graph* g){
	int i, j, k;
	enode* p = NULL;
	int visited[MAX];
	int queue[MAX];
	int head = 0, rear = 0;

	for(i=0; i<g->vexnum; i++)
		visited[i] = 0;

	printf("BFS: ");
	for(i=0; i<g->vexnum; i++){
		if(!visited[i]){
			visited[i] = 1;
			printf(" -> [%c]", g->vexs[i].v);
			queue[head++] = i;
		}

		while(head != rear){
			j = queue[rear++];
			p = g->vexs[j].next;

			while(p){
				k = p->v;
				if(!visited[k]){
					visited[k] = 1;
					printf(" -> [%c]", g->vexs[k].v);
					queue[head++] = k;
				}
				p = p->next;
			}
		}
	}
	printf("\n");
}


void print_vnodelist(vnode vn){
	enode* p = NULL;
	printf("[%c] ", vn.v);
	p = vn.next;
	while(p){
		printf(" -> %d", p->v);
		p = p->next;
	}
}

void destoryvnodelist(vnode vn){
	enode* p = NULL;
	enode* dnode = NULL;

	printf("[%c] ", vn.v);
	p = vn.next;
	while(p){
		dnode = p;
		p = p->next;
		printf(" -[%d]", dnode->v);
		free(dnode);
	}
	printf("\n");
}


void print_graph(Graph* g){
	int i = 0;

	printf("vexs: ");
	for(i=0; i<g->vexnum; i++)
		printf(" [%c] ", g->vexs[i]);
	printf("\n");

	for(i=0; i<g->vexnum; i++){
		printf("%d ", i);
		print_vnodelist(g->vexs[i]);
		printf("\n");
	}
}


void main(){
	int i = 0;
	Graph* g = create_graph();
	print_graph(g);

	DFStraverse(g);

	BFS(g);

	printf("\ndestory:");
	for(i=0; i<g->vexnum; i++)
		destoryvnodelist(g->vexs[i]);

	free(g);
}

