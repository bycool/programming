#include <stdio.h>

void display(int* arr, int len){
    int i = 0;
    for(i=0;i<len;i++)
        printf("[%d]",arr[i]);
    printf("\n");
}

void sortsub(int* arr, int i , int len){
	int child, tmp;

	printf("i:%d  ", i);
	for(; 2*i+1<len; i=child){
		child = 2*i+1;
		if(child+1<len && arr[child] < arr[child+1])
			child++;

		if(arr[i] < arr[child]){
			tmp = arr[i];
			arr[i] = arr[child];
			arr[child] = tmp;
		}else{
			break;
		}
	}
	display(arr, 10);
}

void heapsort(int* arr, int len){
	int i, tmp;

	for(i=len/2-1; i>=0; i--)
		sortsub(arr, i, len);

	printf("\n");

	for(i=len-1; i>0; i--){
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		sortsub(arr, 0, i);
	}
}


int main(){
    int arr[10] = {2,9,6,4,7,8,5,1,0,3};
	printf("b:");
    display(arr,10);
    heapsort(arr,10);
	printf("f:");
    display(arr,10);
}

