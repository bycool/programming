#include <stdio.h>

void subsort(int* arr, int i, int len){
	int child, tmp;

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
}


void heapsort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;
	for(i=len/2-1; i>=0; i--){
		subsort(arr, i, len);
	}

	for(i=len-1; i>0; i--){
		tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		subsort(arr, 0, i);
	}
}

void display(int* arr ,int len){
    int i = 0;
    for(i=0; i<len; i++)
        printf("%d,", arr[i]);
    printf("\b \n");
}


void main(){
    int arr[10] = {7,8,5,9,2,4,1,3,6,0};
    heapsort(arr, 10);
    display(arr, 10);

}
