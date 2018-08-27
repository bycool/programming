#include <stdio.h>
#include <stdlib.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b\n");
}

void mergelist(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c;
	int rb = c+1, re = e;
	int p = b;
	int i = 0;

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

	for(i=0; i<p; i++)
		arr[i] = tmp[i];
}

void mergesort(int* arr, int* tmp, int b, int e){
	if(b<e){
		int c = (b+e)/2;
		mergesort(arr, tmp, b, c);
		mergesort(arr, tmp, c+1, e);
		mergelist(arr, tmp, b, c, e);
	}
}

int main(){
	int arr[10] = {5,7,8,3,6,1,2,9,0,4};
	int* tmp = (int*)malloc(sizeof(int)*10);
	mergesort(arr, tmp, 0, 9);
	display(arr, 10);
	free(tmp);
}
