#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d],", arr[i]);
	printf("\b \n");
}

//  1	2	3	4	5
//  	i
//  	j

void selectsort(int* arr, int len){
	int i, j, min;
	int tmp;

	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[j]<arr[min])
				min = j;
		}
		if(min != i){
			tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}
}

void main(){
	int arr[5] = {3,2,5,1,4};
	selectsort(arr, 5);
	display(arr, 5);
}


