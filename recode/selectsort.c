#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

//  4,3,6,5,7,8,0,9,2,1

void selectsort(int* arr, int len){
	int i = 0, j = 0, min = 0;
	int tmp;
	for(i=0;i<len;i++){
		min = i;
		for(j=i+1;j<len;j++){
			if(arr[j]<arr[min])
				min = j;
		}
		if(min!=i){
			tmp = arr[min];
			arr[min] = arr[i];
			arr[i] = tmp;
		}
	}
}

int main(){
	int arr[10] = {4,3,6,5,7,8,0,9,2,1};
	selectsort(arr,10);
	display(arr,10);
	
}

