#include <stdio.h>

int getnum(){
    int i = 0;
    for(i = 0; i<5; i++){
        if(i==3)
            break;
    }
	return i;
}

int main(){
	printf("%d\n",getnum());
}
