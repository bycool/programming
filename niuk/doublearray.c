#include <stdio.h>

int find(int target, int (*array)[5], int h, int l){
	int i = 0, j = 0;
	for(i=0; i<h; i++){
		if(array[i][l-1] >= target){
			for(j=0; j<l; j++){
				if(target == array[i][j]){
					return 1;
				}
			}
		}
	}
	return 0;
}


int main(){
	int arrt[3][5] = {{1,2,3,4,5}, {6,7,8,9,10}, {11,12,13,14,15} };
	if(find(7, arrt, 3, 5)){
		printf("find\n");
	}

}
