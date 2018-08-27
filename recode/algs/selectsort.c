#include <stdio.h>

void display(int* arr, int len){
	int i = 0;

	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b\n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 1 2 3 4 5
//     i
//     j
void selectsort(int* arr, int len){
	int i = 0, j = 0, min = 0;

	for(i=0; i<len; i++){
		min = i;
		for(j=i+1; j<len; j++){
			if(arr[j] < arr[min])
				min = j;
		}
		if(min != i)
			swap(&arr[min], &arr[i]);
	}
}

int main(){
	int arr[5] = {4,2,5,3,1};
	selectsort(arr, 5);
	display(arr, 5);
}
