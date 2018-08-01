#include <stdio.h>
#include <string.h>
#include <fcntl.h>

static void xml_fzs_title(int fd){
    char buf[128] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    write(fd, buf, strlen(buf)) ;
}

int main(){
	int fd = open("title.xml", O_CREAT | O_WRONLY, 0600);
	xml_fzs_title(fd);
	close(fd);
}


