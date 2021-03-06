#include <stdio.h>
#include <stdlib.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

void mergearr(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1;	
	int rb = c, re = e;
	int p = b;

	while(lb<=le && rb<=re){
		if(arr[lb]<arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];
	}
	while(lb<=le)
		tmp[p++] = arr[lb++];
	while(rb<=re)
		tmp[p++] = arr[rb++];
	int i = 0;
	for(i=0;i<p;i++)
		arr[i] = tmp[i];
}

void mergesort(int* arr, int* tmp, int b, int e){
	if(b<e){
		int c = (b+e)/2;
		mergesort(arr,tmp,b,c);
		mergesort(arr,tmp,c+1,e);
		mergearr(arr,tmp,b,c+1,e);
	}
}


int main(){
	int arr[10] = {1,3,5,7,9,2,4,6,8,0};
	int* tmp = (int*)malloc(sizeof(int)*10);
	mergesort(arr,tmp,0,9);
	display(tmp,10);
	free(tmp);
}

