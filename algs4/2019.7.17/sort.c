#include <stdio.h>
#include <stdlib.h>

void display(char* algs, int* arr, int len) {
	int i = 0;
	printf("%s\t:[", algs);
	for(i=0; i<len; i++) {
		printf("%d,", arr[i]);
	}
	printf("\b]\n");
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubblesort(int* arr, int len) {
	int i = 0, j = 0;
	for(i=0; i<len; i++) {
		for(j=0; j<len-1; j++) {
			if(arr[j] > arr[j+1])
				swap(&arr[j], &arr[j+1]);
		}
	}
}

void insertsort(int* arr, int len) {
	int i = 0, j = 0;
	int tmp = 0;
	for(i=0; i<len; i++) {
		tmp = arr[i];
		for(j=i; j>0 && arr[j-1]>tmp; j--){
			arr[j] = arr[j-1];
		}
		arr[j] = tmp;
	}
}

void selectsort(int* arr, int len) {
	int i = 0, j = 0;
	int min = 0, tmp = 0;

	for(i=0; i<len; i++) {
		min = i;
		for(j=i; j<len; j++){
			if(arr[j] < arr[min])
				min = j;
		}
		if(min != i)
			swap(&arr[i], &arr[min]);
	}
}

void quicksort(int* arr, int b, int e) {
	int bb = b, ee = e;
	int tmp = arr[b];

	if(b >= e) return ;

	while(bb != ee) {
		while(arr[ee] >= tmp && bb < ee)
			ee--;

		while(arr[bb] <= tmp && bb < ee)
			bb++;

		if(bb != ee)
			swap(&arr[bb], &arr[ee]);
		else
			break;
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
		if(arr[lb] <= arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];
	}

	while(lb <= le)
		tmp[p++] = arr[lb++];

	while(rb <= re)
		tmp[p++] = arr[rb++];

	
	for(i=0; i<p; i++)
		arr[i] = tmp[i];
}

void mergesort(int* arr, int* tmp, int b, int e){
	if(b<e){
		int c = (b+e)/2;
		mergesort(arr, tmp, b, c);
		mergesort(arr, tmp ,c+1, e);
		mergelist(arr, tmp, b, c+1, e);
	}
}

void sortsub(int* arr, int i, int len) {
	int child;

	for( i=i;  2*i+1<len; i=child) {
		child = 2*i+1;
		if(child+1<len && arr[child] < arr[child+1])
			child++;

		if(arr[child] > arr[i])
			swap(&arr[child], &arr[i]);
		else
			break;
	}
}

void heapsort(int* arr, int len) {
	int i = 0;

	for(i=len/2-1; i>=0; i--) {
		sortsub(arr, i, len);
	}

	for(i=len-1; i>=0; i--) {
		sortsub(arr, 0, i);
		swap(&arr[0], &arr[i]);
	}
}

void shellsort(int* arr, int len) {
	int step = 1;
	int i = 0, j = 0;
	int tmp = 0;

	while(len/3<step) step = 3 * step + 1;

	while(step>=1) {
		for(i=step; i<len; i++) {
			tmp = arr[i];
			for(j=i; j>=step && arr[j-step] > tmp; j-=step)
				arr[j] = arr[j-step];
			arr[j] = tmp;
		}
		step = step/3;
	}
}

void main() {
	int arr[10] =  {4,7,6,9,1,3,0,2,5,8};
//	bubblesort( arr, 10);
//	display("bubble", arr, 10);
//
//	insertsort(arr, 10);
//	display("insert", arr, 10);

//	selectsort(arr, 10);
//	display("select", arr, 10);

//	quicksort(arr, 0, 9);
//	display("quick", arr, 10);

//	int* tmp = (int*)malloc(10*sizeof(int));
//	mergesort(arr, tmp, 0, 9);
//	display("merge", arr, 10);
//	free(tmp);

//	heapsort(arr, 10);
//	display("heap", arr, 10);

	shellsort(arr, 10);
	display("shell", arr, 10);

}
