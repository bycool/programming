#include <stdio.h>
#include <stdlib.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

int initarray(int* arr, int len, int rand){
	int i = 0;
	int randt = 0;
	if(len==0) return 0;
	if(rand>len) 
		randt = rand%len;
	else
		randt = rand;
	int* change = (int*)malloc(sizeof(int) * randt);

	for(i=0; i<randt; i++){
		change[i] = arr[i];
	}
	for(i=0; randt+i<len; i++){
		arr[i] = arr[randt+i];
	}

	for(i=0; randt+i<len; i++){
		arr[len-randt+i] = change[i];
	}
	free(change);

}
// 5,6,7,9,10,11,14,1,3,4

int findmin(int* arr, int len){
	int b = 0;
	int e = len;
	while(b != e-1){
		if(arr[b] > arr[(b+e)/2])
			e = (b+e)/2;
		else
			b = (b+e)/2;
		printf("arr[%d]:arr[%d] : %d:%d\n", b, e, arr[b], arr[e]);
	}
	return arr[e];
}


int main(){
	int array[10] = {1,3,4,5,6,7,9,10,11,14};
	display(array, 10);
	initarray(array, 10, 7);
	display(array, 10);
	printf("%d\n",findmin(array, 10));
}

