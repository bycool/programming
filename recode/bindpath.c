#include <stdio.h>
#include <string.h>

void bindpath(char* filename, char* outdir){
	char* p = NULL;
	char outpath[64];
	int rc = -1;

	rc = snprintf(outpath, 64, "%s", outdir);
	p = outpath + rc - 1;
	sprintf(p, "%s", filename);

	printf("outpath: %s\n", outpath);
}

int main(){
	char outdir[8] = "/tmp/";
	char filename[16] = "/home/1.txt";

	bindpath(filename, outdir);

	return 0;
}

