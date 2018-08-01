#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){
	int fd = open("root.fzs", O_CREAT | O_WRONLY, 0600);
	xml_fzs_root(fd, 1);
	close(fd);
}
static void xml_fzs_root(int fd, int bgn){
    char buf[16] = bgn ? "<root>" : "</root>";
}
