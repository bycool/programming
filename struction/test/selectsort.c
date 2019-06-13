#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void selectsort(int* arr, int len){
	int i = 0, j = 0;
	int min = 0, tmp = 0;

	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[min]>arr[j])
				min = j;
		}
		if(min != i){
			tmp = arr[min];
			arr[min] = arr[i];
			arr[i] = tmp;
		}
	}
}

void main(){
	int arr[5] = {3,4,2,5,1};
	selectsort(arr, 5);
	display(arr, 5);
}
