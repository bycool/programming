#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

void insertsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;
	for(i=1;i<len;i++){
		tmp = arr[i];
		j = i - 1;
		while(arr[j]>tmp && j>=0){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
	}

}

int main(){
	int arr[10] = {7,2,9,3,1,6,5,8,0,4};
	insertsort(arr,10);
	display(arr,10);
}

