#include <stdio.h>
#include <stdlib.h>

void mergesub(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1, rb = c, re = e;
	int p = b;

	while(lb <= le && rb <= re){
		if(arr[lb] < arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];
	}

	while(lb <= le)
		tmp[p++] = arr[lb++];

	while(rb <= re)
		tmp[p++] = arr[rb++];

	int i = 0;
	for(i=0; i<p; i++)
		arr[i] = tmp[i];
}

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d],", arr[i]);
	printf("\b \n");
}

void merge(int* arr, int *tmp,  int b, int e){
	if(b<e){
		int c = (b+e)/2;
		merge(arr, tmp, b, c);
		merge(arr, tmp, c+1, e);
		mergesub(arr, tmp, b, c+1, e);
	}
}

void main(){
	int arr[5] = {3,1,5,4,2};
	int* tmp = (int*)malloc(5*sizeof(int));
	merge(arr, tmp, 0, 4);
	display(arr, 5);
	free(tmp);
	
}

