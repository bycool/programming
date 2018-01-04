#include <stdio.h>
char* returnstr()
  {
               char p[] = "hello";
                printf("%d\n",sizeof(p));
                printf("%d\n",strlen(p));
            }
int main()
            {
            char* s = returnstr();
           printf("%s\n",s);
           }
