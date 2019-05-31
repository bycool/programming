#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define LENGTH(p)  ( (sizeof(p)) / (sizeof(p[0])) )

typedef struct Graph {
	char vexs[MAX];
	int vexnum;
	int edgnum;
	int matrix[MAX][MAX];
}Graph;

int getxy(Graph* g, char c){
	int i = 0;

	for(i=0; i<g->vexnum; i++)
		if(g->vexs[i] == c)
			return i;

	return -1;
}

Graph* create_graph(){
	int i = 0, x, y;
	char a, b;

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

	for(i=0; i<vlen; i++)
		g->vexs[i] = vexs[i];

	for(i=0; i<elen; i++){
		a = edgs[i][0];
		b = edgs[i][1];

		x = getxy(g, a);
		y = getxy(g, b);

		if(x!=-1 && y!=-1)
			g->matrix[x][y] = 1;
	}

	return g;
}

int first_vextex(Graph* g, int c){
	int i;

	if(c<0 || c>=g->vexnum)
		return -1;

	for(i=0; i<g->vexnum; i++)
		if(g->matrix[c][i] == 1)
			return i;

	return 0;
}

int next_vextex(Graph* g, int c, int w){
	int i;

	if(c<0 || w<0 || c>=g->vexnum || w>=g->vexnum)
		return -1;

	for(i=w+1; i<g->vexnum; i++)
		if(g->matrix[c][i] == 1)
			return i;

	return -1;
}

void DFS(Graph* g, int c, int* visited){
	int i = 0;

	visited[c] = 1;
	printf(" -> [%c]", g->vexs[c]);

	for(i=first_vextex(g, c); i>=0; i=next_vextex(g, c, i)){
		if(!visited[i])
			DFS(g, i, visited);
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

	for(i=0; i<g->vexnum; i++)
		visited[i] = 0;

	printf("BFS: ");
	for(i=0; i<g->vexnum; i++){

		if(!visited[i]){
			visited[i] = 1;
			printf(" -> [%c]", g->vexs[i]);
			queue[head++] = i;
		}

		while(head != rear){
			j = queue[rear++];
			for(k=first_vextex(g, j); k>=0; k=next_vextex(g, j, k)){
				if(!visited[k]){
					visited[k] = 1;
					printf(" -> [%c]", g->vexs[k]);
					queue[head++] = k;
				}
			}
		}

	}
	printf("\n");
	
}



void print_graph(Graph* g){
	int i = 0, j = 0;

	printf("vexs: ");
	for(i=0; i<g->vexnum; i++)
		printf(" [%c]", g->vexs[i]);
	printf("\n");

	printf("vexnum: %d\n", g->vexnum);
	printf("edgnum: %d\n", g->edgnum);

	printf("matrix.ud\n");
	for(i=0; i<g->vexnum; i++){
		printf(" ");
		for(j=0; j<g->vexnum; j++){
			printf("  %d", g->matrix[i][j]);
		}
		printf("\n");
	}
	

}

void main(){
	Graph* g = create_graph();

	DFStravese(g);
	BFS(g);

	print_graph(g);

	free(g);

}
