#include <stdio.h>

void display(int* arr, int len){
    int i = 0;
    for(i=0; i<len; i++)
        printf("[%d]", arr[i]);
    printf("\n");
}

void insertsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;

	for(i=1; i<len; i++){
		tmp = arr[i];
		for(j=i; j>=0 && arr[j-1]>tmp; j--)
			arr[j] = arr[j-1];

		arr[j] = tmp;
	}
}

void main(){
	int arr[5] = {3,2,4,5,1};
	insertsort(arr, 5);
	display(arr, 5);
}
