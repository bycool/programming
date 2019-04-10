#include <stdio.h>
#include <stdlib.h>

void display(int* arr ,int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

void swap(int* a, int* b){
	int tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubblesort(int* arr, int len){  //1.冒泡
	int i = 0, j = 0;
	for(i=0; i<len; i++)
		for(j=0; j<len-1; j++)
			if(arr[j+1] < arr[j])
				swap(&arr[j+1], &arr[j]);
}

void selectsort(int* arr, int len){ //2.选择
	int i = 0, j = 0, min = 0;
	for(i=0; i<len; i++){
		min = i;
		for(j=i; j<len; j++){
			if(arr[j] < arr[min])
				min = j;
		}
		if(min != i)
			swap(&arr[min], &arr[i]);
	}
}

void insertsort(int* arr, int len){ //3.插入
	int i = 0, j = 0;
	int tmp = 0;
	for(i=1; i<len; i++){
		tmp = arr[i];
		for(j=i-1; j>=0 && arr[j]>tmp; j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = tmp;
	}
}

void quicksort(int* arr, int b, int e){ //4.快速排序
	int bb = b, ee = e;
	int tmp = arr[b];

	if(b>=e) return ;

	while(bb!=ee){
		while(arr[ee]>=tmp && bb<ee)
			ee--;
		while(arr[bb]<=tmp && bb<ee)
			bb++;
		if(bb<ee)
			swap(&arr[bb], &arr[ee]);
	}
	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr, b, bb-1);
	quicksort(arr, ee+1, e);
}

void mergelist(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1;
	int rb = c, re = e;
	int p = b;

	while(lb<=le && rb<=re){
		if(arr[lb]<arr[rb]){
			tmp[p++] = arr[lb++];
		}else{
			tmp[p++] = arr[rb++];
		}
	}
	while(lb<=le){
		tmp[p++] = arr[lb++];
	}
	while(rb<=re){
		tmp[p++] = arr[rb++];
	}

	int i = 0;
	for(i=0; i<p; i++)
		arr[i] = tmp[i];
}

void mergesort(int* arr, int* tmp, int b, int e){ //5.归并排序
	if(b<e){
		int c = (b+e)/2;
		mergesort(arr, tmp, b, c);
		mergesort(arr, tmp, c+1, e);
		mergelist(arr, tmp, b, c+1, e);
	}
}

void sortree(int* arr, int i, int len){
	int child;
	for(i=i; i*2+1<len; i=child){
		child = i*2+1;
		if(arr[child]<=arr[child+1] && child+1<len)
			child++;
		if(arr[i] < arr[child])
			swap(&arr[i], &arr[child]);
		else
			break;
	}
}

void heapsort(int* arr, int len){ //6.堆排序
	int i = 0;

	for(i=len/2-1; i>=0; i--)
		sortree(arr, i, len);

	for(i=len-1; i>=0; i--){
		swap(&arr[0], &arr[i]);
		sortree(arr, 0, i);
	}
}

void shellsort(int* arr, int len){  //7.希尔排序
	int step = 1, i = 0, j = 0;
	int tmp = 0;
	while(step<len/3) step=step*3+1;

	while(step>=1){
		for(i=step; i<len; i++){
			tmp = arr[i];
			for(j=i; j>=step && arr[j-step]>tmp; j-=step)
				arr[j] = arr[j-step];
			arr[j] = tmp;
		}
		step = step/3;
	}
}

void main(){
	int arr[10] = {7,8,5,9,2,4,1,3,6,0};
	shellsort(arr, 10);
	display(arr, 10);
}
