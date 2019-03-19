#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
 
int main(void)
{
        char host[100] = {0};
         if(gethostname(host,sizeof(host)) < 0){
                ERR_EXIT("gethostname");
        }
 
        struct hostent *hp;
        if ((hp=gethostbyname(host)) == NULL){
                ERR_EXIT("gethostbyname");
        }
 
        int i = 0;
        while(hp->h_addr_list[i] != NULL)
        {
                printf("hostname: %s\n",hp->h_name);
                printf("      ip: %s\n",inet_ntoa(*(struct in_addr*)hp->h_addr_list[i]));
                i++;
        }
        return 0;
}
