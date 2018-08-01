#include <stdio.h>

void display(int* arr, int len)
{
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

// 1 2 3 4 5
//   i
//   j
void insertsort(int* arr, int len)
{
	int i = 0, j = 0;
	int tmp = 0;
	for(i=1; i<len; i++)
	{
		tmp = arr[i];
		for(j=i-1; arr[j] > tmp && j >= 0; j--)
			arr[j+1] = arr[j];
		arr[j+1] = tmp;
	}
}

int main(){
	int arr[5] = {4,3,2,5,1};
	insertsort(arr, 5);
	display(arr, 5);
}
