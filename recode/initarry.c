#include <stdio.h>

int main(){
	int arr[10] = { 0 };
	int i = 0;
	for(i=0; i<10; i++){
		arr[i] = i;
		printf("arr[%d]: %d\n", i, arr[i]);
	}
	
	for(i=0; i<10; i++){
		arr[i] = i;
		printf("arr[%d]: %d\n", i, arr[i]);
	}
}
