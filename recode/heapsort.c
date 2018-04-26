#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

void heapadjust(int* arr, int i, int len){
	int child, tmp;
	for(i=i;2*i+1<len;i=child){
		child = 2*i+1;   //需要调整的子树的左孩子
		if(child+1<len && arr[child] < arr[child+1])  //i节点存在右孩子，且右孩子大于左孩子。
			child++;
		if(arr[i]<arr[child]){
			tmp = arr[child];
			arr[child] = arr[i];
			arr[i] = tmp;
		}else{
			break;
		}
	}
}

void heapsort(int* arr, int len){
	int i,tmp;
	for(i=len/2-1;i>=0;i--)  //入口节点:是一棵树或子树，范围应该为0~len/2-1
		heapadjust(arr,i,len);
	for(i=len-1;i>0;i--){
		tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		heapadjust(arr,0,i);
	}
}

int main(){
	int arr[15] = {3,2,1,6,4,5,7,9,8,10,12,11,15,14,13};
	heapsort(arr,15);
	display(arr,15);
}
