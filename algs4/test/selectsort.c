#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 1 2 3 4 5
//   i
//   j
void selectsort(int* arr, int len)
{
	int i = 0, j = 0;
	int min = 0;

	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[j]<arr[min])
				min = j;
		}
		if(min!=i)
			swap(&arr[i], &arr[min]);
	}
}

int main(){
	int arr[5] = {3,2,4,1,5};
	selectsort(arr, 5);
	display(arr, 5);
}

