#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define LENGTH(p)  ( (sizeof(p))/(sizeof(p[0])) )

typedef struct graph {
	char vexs[MAX];
	int vexnum;
	int edgnum;
	int matrix[MAX][MAX];
}Graph;

int getxy(char* vexs, char c, int vlen){
	int i = 0;
	for(i=0; i<vlen; i++){
		if(vexs[i] == c)
			return i;
	}
	return -1;
}

Graph* create_graph(){
	int i = 0;
	int x = 0, y = 0;

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

	for(i=0; i<vlen; i++){
		g->vexs[i] = vexs[i];
	}

	for(i=0; i<elen; i++){
		x = getxy(vexs, edgs[i][0], vlen);
		y = getxy(vexs, edgs[i][1], vlen);

		if(x != -1 && y != -1){
			g->matrix[x][y] = 1;
			g->matrix[y][x] = 1;
		}
	}
	return g;
}


int first_vertex(Graph* g, int c){
	int i;

	if(c<0 || c>=g->vexnum)
		return -1;

	for(i=0; i<g->vexnum; i++)
		if(g->matrix[c][i] == 1)
			return i;
	return -1;
}

int next_vertex(Graph* g, int v, int w){
	int i;

	if(v<0 || w<0 || v>=g->vexnum || w>=g->vexnum)
		return -1;

	for(i=w+1; i<g->vexnum; i++)
		if(g->matrix[v][i] == 1)
			return i;
	return -1;
}


void DFS(Graph* g, int c, int *visited){
	int i;

	visited[c] = 1;
	printf(" -> [%c]", g->vexs[c]);

	fflush(0);

	for(i=first_vertex(g, c); i>=0; i=next_vertex(g, c, i))
		if(!visited[i])
			DFS(g, i, visited);
}

void DFStraverse(Graph* g){
	int i;

	int visited[MAX] = { 0 };

	for(i=0; i<g->vexnum; i++){
		visited[i] = 0;
	}

	printf("DFS:");
	for(i=0; i<g->vexnum; i++){
		if(!visited[i])
			DFS(g, i, visited);
	}
	printf("\n");
}


void BFS(Graph* g){
	int head = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];
	int i, j, k;

	for(i=0; i<g->vexnum; i++)
		visited[i] = 0;

	printf("BFS:");
	for(i=0; i<g->vexnum; i++){
		if(!visited[i]){
			visited[i] = 1;
			printf(" -> [%c]", g->vexs[i]);
			queue[rear++] = i;
		}

		while(head != rear){
			j = queue[head++];

			for(k=first_vertex(g, j); k>=0; k=next_vertex(g, j, k)){
				if(!visited[k]){
					visited[k] = 1;
					printf(" -> [%c]", g->vexs[k]);
					queue[rear++] = k;
				}
			}
		}
	}
	printf("\n");
}



void print_graph(Graph* g){
	int i = 0, j = 0;

	printf("g.vexnum: %d\n", g->vexnum);
	printf("g.edgnum: %d\n", g->edgnum);

	printf("g.vexs:");
	for(i=0; i<g->vexnum; i++){
		printf(" %c", g->vexs[i]);
	}
	printf("\n");

	printf("matrix:\n");
	for(j=0; j<g->vexnum; j++){
		for(i=0; i<g->vexnum; i++)
			printf(" %d ", g->matrix[i][j]);
		printf("\n");
	}
}

void main(){
	Graph* g = NULL;
	g = create_graph();
	print_graph(g);

	DFStraverse(g);

	BFS(g);

	free(g);
}



