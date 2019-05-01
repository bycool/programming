#include <stdio.h>

void display(int *arr, int len){
	int i;
	for(i=0; i<len; i++){
		printf("[%d].", arr[i]);
	}
	printf("\b \n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void selectsort(int* arr, int len){
	int i, j, min;
	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[j] < arr[min]){
				min = j;
			}
		}
		if(min != i){
			swap(&arr[i], &arr[min]);
		}
	}
}

void main(){
	int arr[5] = { 4,2,3,5,1};
	selectsort(arr, 5);
	display(arr, 5);
}
