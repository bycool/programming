#include <stdio.h>
#include <stdlib.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubblesort(int* arr,  int len){
	int i = 0, j = 0;
	for(i=0; i<len; i++){
		for(j=0; j+1<len; j++){
			if(arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}

void selectsort(int* arr, int len){
	int i = 0, j = 0, min = 0;
	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[min] > arr[j]){
				min = j;
			}
		}
		if(min != i){
			swap(&arr[min], &arr[i]);
		}
	}

}

void insertsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;
	for(i=1; i<len; i++){
		tmp = arr[i];
		for(j=i-1; arr[j]>tmp && j>=0; j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = tmp;
	}
}

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b];

	if(b >= e) return ;

	while(bb != ee){

		while(arr[ee] >= tmp && bb < ee)
			ee--;

		while(arr[bb] <= tmp && bb < ee)
			bb++;

		if(bb<ee)
			swap(&arr[bb], &arr[ee]);
	}

	swap(&arr[bb], &arr[b]);

	quicksort(arr, b, bb-1);
	quicksort(arr, ee+1, e);
}

void mergelist(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1;
	int rb = c, re = e;
	int p = b, i = 0;

	while(lb <= le && rb <= re){
		if(arr[lb] < arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];
	}

	while(lb <= le){
		tmp[p++] = arr[lb++];
	}

	while(rb <= re){
		tmp[p++] = arr[rb++];
	}

	for(i=0; i<p; i++){
		arr[i] = tmp[i];
	}
}

void mergesort(int* arr, int* tmp, int b, int e){
	if(b<e){
		int c = (b+e)/2;
		mergesort(arr, tmp, b, c);
		mergesort(arr, tmp, c+1, e);
		mergelist(arr, tmp, b, c+1, e);
	}
}


void main(void){
	int arr[5] = {3,2,4,1,5};
	display(arr, 5);
}
