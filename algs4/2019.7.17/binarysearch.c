#include <stdio.h>

int binarysearch(int* arr, int len, int val){
	int i = 0 ;
	while(i<len){
		int mid = i + (len - i)/2;
		if(arr[mid] > val)
			len = mid - 1;
		else if(arr[mid] < val)
			i = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main() {
	int arr[10] = {2,5,8,12,14,25,26,29,31,35};

	int rc = binarysearch(arr, 10, 26);

	printf("rc = %d\n", rc);
}
