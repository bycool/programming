#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d].", arr[i]);
	printf("\b \n");
}

//  3  1  2  4  5
//  i
//     j
void insertsort(int* arr, int len){
	int i, j, tmp;
	for(i=0; i<len; i++){
		tmp = arr[i];
		for(j=i;  j>0 && arr[j-1]>tmp ; j--){
			arr[j] = arr[j-1];
		}
		arr[j] = tmp;
	}
}

void main(){
	int arr[5] = {4,2,3,1,5};
	insertsort(arr, 5);
	display(arr, 5);
}
