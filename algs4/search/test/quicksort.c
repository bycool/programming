#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d].", arr[i]);
	printf("\b \n");
}

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b], t;

	if(b >= e ) return;

	while( bb < ee){
		while(arr[ee] >= tmp && bb < ee)
			ee--;
		while(arr[bb] <= tmp && bb < ee)
			bb++;
		if(bb<ee){
			t = arr[bb];
			arr[bb] = arr[ee];
			arr[ee] = t;
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
	int arr[5] = {2,4,3,1,5};
	quicksort(arr, 0, 4);
	display(arr, 5);
}

