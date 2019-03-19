#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

void bubblesort(int* arr, int len){
	int i = 0, j = 0;
	for(i=0; i<len; i++)
		for(j=0; j<len-1; j++)
			if(arr[j] > arr[j+1])
				swap(&arr[j], &arr[j+1]);
}

//  5   3   4    2    1
//      i
//      j

void insertsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;
	for(i=0; i<len; i++){
		tmp = arr[i];
		for(j=i; j>0 && arr[j-1] > tmp; j--)
			arr[j] = arr[j-1];
		arr[j] = tmp;
	}
}


void selectsort(int* arr, int len){
	int i = 0, j = 0;
	int min = 0;
	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++)
			if(arr[j] < arr[min])
				min = j;
		if(min != i)
			swap(&arr[min], &arr[i]);
	}
		
}

//  1  2  3  4  5  6  7  8  9  0
//

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b];

	if(b >= e) return;

	while(bb < ee){
		while(arr[ee] >= tmp && bb < ee)
			ee--;
		while(arr[bb] <= tmp && bb < ee)
			bb++;
		if(bb<ee)
			swap(&arr[bb], &arr[ee]);
	}

	swap(&arr[b], &arr[bb]);

	quicksort(arr, b, bb-1);
	quicksort(arr, bb+1, e);

}


void mergelist(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1;
	int rb = c, re = e;
	int p = b;
	while(lb <= le && rb <= re)
		if(arr[lb] < arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];

	while(lb <= le)
		tmp[p++] = arr[lb++];

	while(rb <= re)
		tmp[p++] = arr[rb++];

	int i = 0;
	for(i=0; i<p; i++)
		arr[i] = tmp[i];
}

void mergesort(int* arr, int* tmp, int b, int e){
	if(b<e){
		int c = (b+e)/2;
		mergesort(arr, tmp, b, c);
		mergesort(arr, tmp, c+1, e);
		mergelist(arr, tmp, b, c+1, e);
	}
}

void heapsubtree(int* arr, int i, int len){
	int i = 0;
	
}



int main(){
	int arr[10] = {5,3,4,2,8,9,7,6,0,1};
	display(arr, 10);
	printf("---------\n");
	//bubblesort(arr, 10);
	//insertsort(arr, 10);
	//selectsort(arr, 10);
	//quicksort(arr, 0, 9);
//	int* tmp = (int*)malloc(10*sizeof(int));
//	mergesort(arr, tmp, 0, 9);
//	free(tmp);
	
	display(arr, 10);
}









