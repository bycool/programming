#include <stdio.h>

#define MAXSIZE 255

typedef struct sqlist{
	int data[MAXSIZE];
	int len;
}sqlist;

int insqlist(sqlist* sq, int offset, int elem){
	if(offset<0 || offset > MAXSIZE || sq->len == MAXSIZE || offset > sq->len+1){
		printf("sth wrong:\n\t1.offset<0,\n\t2.offset>maxsize,\n\t3.sqlist full\n\t4.offset > sq->len\n");
		return -1;
	}
	int cnt = 0;
	for(cnt = sq->len;offset<=cnt;cnt--){
		sq->data[cnt] = sq->data[cnt-1]; 
	}
	sq->data[cnt] = elem;
//	printf("sq->data[%d]:%d\n",cnt,elem);
	sq->len++;
	return sq->len;
}

int insqlist2tail(sqlist* sq, int elem){
	return insqlist(sq,sq->len+1,elem);
}

int insqlist2head(sqlist* sq, int elem){
	return insqlist(sq,1,elem);
}

int removeflist(sqlist* sq, int offset){
	if(offset < 0 || offset > sq->len){
		printf("offset <0 || offset > sq->len\n");
		return -1;
	}
	int i = 0;
	for(i=offset;i<sq->len;i++){
		sq->data[i-1] = sq->data[i];
	}
	sq->len--;
	return sq->len;
}


void display(sqlist* sq){
	int i =0;
	for(i=0;i<sq->len;i++)
		printf("%d,",sq->data[i]);
	printf("\n");
}

int main(){
	sqlist sq;
	sq.data[0]=0;
	sq.data[1]=1;
	sq.data[2]=2;
	sq.data[3]=3;
	sq.data[4]=4;
	sq.len = 5;
	display(&sq);

//	int ret = insqlist(&sq,6,5);
	int ret = insqlist2tail(&sq,5);
	if(ret > 0)
		display(&sq);
	ret = insqlist2head(&sq,-1);
	if(ret > 0)
		display(&sq);

	ret = removeflist(&sq,4);
	if(ret > 0)
		display(&sq);

}


