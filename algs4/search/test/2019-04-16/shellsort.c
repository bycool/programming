#include <stdio.h>

void shellsort(int* arr, int len){
	int step = 1, i = 0, j = 0;
	int tmp = 0;

	while(step<len/3) step = len/3+1;

	while(step>=1){
		for(i=step; i<len; i++){
			tmp = arr[i];
			for(j=i; j>=step && arr[j-step] > tmp; j-=step)
				arr[j] = arr[j-step];
			arr[j] = tmp;
		}
		step = step/3;
	}
}

void display(int* arr ,int len){
    int i = 0;
    for(i=0; i<len; i++)
        printf("%d,", arr[i]);
    printf("\b \n");
}


int main(){
    int arr[10] = {7,8,5,9,2,4,1,3,6,0};
    shellsort(arr, 10);
    display(arr, 10);

}
