#include <stdio.h>

// 4  2  3  6  1  5
// i
// j

void selectsort(int* arr, int len){
	int i = 0, j = 0;
	int min = 0;
	int tmp = 0;
	for(i=0;i<len;i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[j]<arr[min])
				min = j;
		}
		if(min!=i){
			tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
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
    selectsort(arr, 5);
    display(arr, 5);

}
