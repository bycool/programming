#include <stdio.h>
#include <fcntl.h>

void filegetc();
void fileputc();
void filefwrite();

main(){
//	filegetc();
//	fileputc();
	filefwrite();
}

void filegetc(){
	int fd = open("a", O_RDWR | O_CREAT | O_EXCL, S_IRUSR);
	write(fd,"hello",5);
	close(fd);
	FILE* fst = fopen("a","r");
	int c = getc(fst);
	if(ferror(fst)){
		printf("error reading from a\n");
		clearerr(fst);
	}
	printf("char c = %c\n",c);
	c = getc(fst);
	printf("char c = %c\n",c);
	fclose(fst);
	fst = fopen("a","r");
	c = getc(fst);
	printf("char c = %c\n",c);
	fclose(fst);
}

void fileputc(){
	FILE* fp = fopen("b","a+");
	putc('h',fp);
	putc('e',fp);
	putc('l',fp);
	putc('l',fp);
	putc('o',fp);
	fclose(fp);
	int fd = open("b",O_RDONLY);
	char buf[10];
	read(fd,buf,sizeof(buf));
	printf("buf is %s\n",buf);
	close(fd);

}
	struct item{
		int a;
		char b;
	};

void filefwrite(){
	struct item i;
	i.a = 10;
	i.b = 'c';

	FILE* fp = fopen("w.txt","ab+");
	fwrite(&i,sizeof(i),1,fp);
	fclose(fp);
	
	struct item t;
	
	fp = fopen("w.txt","ab+");
	fread(&t,sizeof(t),1,fp);
	printf("%d,%c\n",t.a,i.b);
	fclose(fp);

}














