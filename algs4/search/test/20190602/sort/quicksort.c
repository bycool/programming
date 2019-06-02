#include <stdio.h>

void display(int* arr, int len){
    int i = 0;
    for(i=0; i<len; i++)
        printf("[%d],", arr[i]);
    printf("\b \n");
}

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b], p;

	if(b>=e) return ;

	while(bb<ee){
		while(bb<ee && arr[ee] >= tmp)
			ee--;

		while(bb<ee && arr[bb] <= tmp)
			bb++;

		if(bb<ee){
			p = arr[bb];
			arr[bb] = arr[ee];
			arr[ee] = p;
		}else{
			break;
		}
	}

	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr, b, bb-1);
	quicksort(arr, ee+1, e);
}

void main(){
	int arr[5] = {3,2,5,1,4};
	quicksort(arr, 0, 4);
	display(arr,  5);
}


