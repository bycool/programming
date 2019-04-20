#include <stdio.h>

//  1  2  3  4  5  6
//     i
//  j
void insertsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;

	for(i=1; i<len; i++){
		tmp = arr[i];
		for(j=i-1; j>=0 && arr[j]>tmp; j--)
			arr[j+1] = arr[j];
		arr[j+1] = tmp;
	}
}

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void main(){
	int arr[5] = { 4,2,3,1,5 };
	insertsort(arr, 5);
	display(arr, 5);
}
