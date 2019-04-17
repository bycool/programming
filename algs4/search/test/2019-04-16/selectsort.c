#include <stdio.h>

void selectsort(int* arr, int len){
	int i = 0, j = 0;
	int min = 0, tmp;

	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[j] < arr[min])
				min = j;
		}
		if(min != i){
			tmp = arr[min];
			arr[min] = arr[i];
			arr[i] = tmp;
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
    int arr[10] = {5,2,8,1,0,4,3,6,9,7};
    selectsort(arr, 10);
    display(arr, 10);
}

