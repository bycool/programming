#include <stdio.h>

void bubblesort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;
	for(i=0; i<len; i++){
		for(j=1; j<len; j++){
			if(arr[j-1] > arr[j]){
				tmp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = tmp;
			}
		}
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
    bubblesort(arr, 5);
    display(arr, 5);
}

