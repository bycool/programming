#include <stdio.h>

//  1  2  3  4  5  6
//     i
//     j

void insertsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;

	for(i=1; i<len; i++){
		tmp = arr[i];
		for(j=i; j>=0 && arr[j-1] > tmp; j--){
			arr[j] = arr[j-1];
		}
		arr[j] = tmp;
	}
}

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void main(){
	int arr[10] = {5,2,8,1,0,4,3,6,9,7};
	insertsort(arr, 10);
	display(arr, 10);
}
