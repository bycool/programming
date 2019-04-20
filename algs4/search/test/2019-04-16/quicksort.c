#include <stdio.h>

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b], t;

	if(b>=e) return ;

	while(bb!=ee){
		while(arr[ee] >= tmp && bb < ee)
			ee--;

		while(arr[bb] <= tmp && bb < ee)
			bb++;

		if(bb<ee){
			t=arr[bb];
			arr[bb] = arr[ee];
			arr[ee] = t;
		}
	}

	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr, b, bb-1);
	quicksort(arr, ee+1, e);
}

void display(int* arr, int len){
    int i = 0;
    for(i=0; i<len; i++)
        printf("[%d]", arr[i]);
    printf("\n");
}

void main(){
    int arr[10] = {5,2,8,1,0,4,3,6,9,7};
    quicksort(arr, 0, 9);
    display(arr, 10);
}

