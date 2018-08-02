#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	char ch = 0;
    int i = -1;
	while( (ch = getopt(argc,argv,"c:s:r::p::")) !=-1){
        printf("getopt:%c\n",ch);
		switch(ch)
		{
			case 'c':
                i = atoi(optarg);
				printf("%d\n",i);
				break;
			case 's':
				break;
			case 'r':
				break;
			case 'p':
				break;
			default:
				break;

		}
	}
}
