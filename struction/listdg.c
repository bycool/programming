#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define LENGTH(p)  ( (sizeof(p)) / (sizeof(p[0]))  )

typedef struct enode {
	int v;
	struct enode* next;
}enode;

typedef struct vnode {
	char c;
	struct enode* next;
}vnode;

typedef struct Graph {
	int vexnum;
	int edgnum;
	vnode vexs[MAX];
}Graph;

int getxy(Graph* g, char c){
	int i = 0;

	for(i=0; i<g->vexnum; i++){
		if(g->vexs[i].c == c)
			return i;
	}
	return -1;
}

Graph* create_graph(){
	int i = 0;
	int x, y;
	enode* p = NULL;
	enode* new = NULL;

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
		g->vexs[i].c = vexs[i];
		g->vexs[i].next = NULL;
	}

	for(i=0; i<g->edgnum; i++){
		x = getxy(g, edgs[i][0]);
		y = getxy(g, edgs[i][1]);

		new = (enode*)malloc(sizeof(enode));
		new->v = y;
		new->next = NULL;

		p = g->vexs[x].next;
		if(p == NULL){
			g->vexs[x].next = new;
		}else{
			while(p->next){
				p = p->next;
			}
			p->next = new;
		}

	}
	return g;
}


void DFS(Graph* g, int c, int* visited){
	enode* p = NULL;
	int k = 0;

	visited[c] = 1;
	printf(" -> %c", g->vexs[c].c);

	p = g->vexs[c].next;
	while(p){
		k = p->v;
		if(!visited[k])
			DFS(g, k, visited);

		p = p->next;
	}
}

void DFStravese(Graph* g){
	int i = 0;
	int visited[MAX];

	for(i=0; i<g->vexnum; i++)
		visited[i] = 0;

	printf("DFS: ");
	for(i=0; i<g->vexnum; i++)
		if(!visited[i])
			DFS(g, i, visited);

	printf("\n");
}

void BFS(Graph* g){
	int i, j, k;
	int visited[MAX];
	int queue[MAX];
	int head = 0, rear = 0;
	enode* p = NULL;

	for(i=0; i<g->vexnum; i++){
		visited[i] = 0;
	}

	printf("BFS: ");
	for(i=0; i<g->vexnum; i++){
		if(!visited[i]){
			visited[i] = 1;
			printf(" -> %c", g->vexs[i].c);
			queue[head++] = i;
		}

		while(head != rear){
			j = queue[rear++];
			p = g->vexs[j].next;

			while(p){
				k = p->v;
				if(!visited[k]){
					visited[k] = 1;
					printf(" -> %c", g->vexs[k].c);
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
	printf("[%c]", vn.c);

	p = vn.next;
	while(p){
		printf(" -> [%d]", p->v);
		p = p->next;
	}
	printf("\n");
}

void print_graph(Graph* g){
	int i = 0;

	printf("vexnum: %d\n", g->vexnum);
	printf("edgnum: %d\n", g->edgnum);

	for(i=0; i<g->vexnum; i++){
		print_vnodelist(g->vexs[i]);
	}
}

void destoryvnode(vnode vn){
	enode* p = NULL;
	enode* dnode = NULL;
	printf("[%c]", vn.c);

	p = vn.next;
	while(p){
		dnode = p;
		p = p->next;
		printf(" -[%d] ", dnode->v);
		free(dnode);
	}
	printf("\n");
}

void destorygraph(Graph* g){
	int i = 0;
	for(i=0; i<g->vexnum; i++)
		destoryvnode(g->vexs[i]);
}



void main(){
	Graph* g = create_graph();

	DFStravese(g);
	BFS(g);

	print_graph(g);

	destorygraph(g);

	free(g);
}
