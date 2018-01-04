#include <stdio.h>
#include <stdlib.h>

int add(int a,int b){
	int ta,tb;
	do{
		ta = a^b;
		tb = (a&b)<<1;

		a=ta;
		b=tb;

	}while(b != 0);
	return a;
}

char* rever(char *s){
	char* tmp ,*re,*r;
	tmp = s;
	r=re = (char*)malloc(32);
	while(*tmp!='\0'){
	   printf("%p\t,%c\n",tmp,*tmp);
	   tmp++;
	}
	while(tmp!=s){
		tmp--;
		printf("%p\t,%c\n",tmp,*tmp);
		*re = *tmp;
		re++;
	}
	*re == '\0' ;
	printf("%s\n",r);
}

int mystrlen(char* s){
	char* tmp = s;
	int i = 0;
	while(*tmp!='\0'){
		tmp++;
		i++;
	}
	return i;
}

int main(){
	char* a = "abc";
//	rever(a);
	printf("%d\n",mystrlen(a));
}
