#include <stdio.h>

int h = 10, w = 10;
int arr[10][10] = {0};
int num = 0;

void init_arr(){
	int i = 0, j = 0;
	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			arr[i][j] = num++;
//			printf("[%d][%d]=%d  ", i,j,arr[i][j]);
		}
//		printf("\n");
	}

}

int main(){
	init_arr();

	int i = 0, j = 0;
	int target = 65;

	for(i=0; i<h; i++){
		if(arr[i][j]<target)
			continue;
		else
			i--;
		for(j=0; j<w; j++)
			if(arr[i][j]==target){
				printf("[%d][%d]\n", i,j);
				break;
			}
		break;
	}
}
