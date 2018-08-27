#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b\n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sortree(int* arr, int i, int len){
	int child;

	for(i=i; i*2+1<len; i=child){
		child = 2*i+1;
		if(arr[child+1]>=arr[child] && child+1 <len)
			child++;
		if(arr[child] > arr[i])
			swap(&arr[child], &arr[i]);
		else
			break;
	}
}

void heapsort(int* arr, int len){
	int i = 0;
	for(i=len/2-1; i>=0; i--)
		sortree(arr, i, len);

	for(i=len-1; i>=0; i--){
		swap(&arr[i], &arr[0]);
		sortree(arr, 0, i);
	}
}

int main(){
	int arr[10] = {7,8,5,9,2,4,1,3,6,0};
	heapsort(arr, 10);
	display(arr, 10);
}
