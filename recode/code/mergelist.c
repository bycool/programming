#include <stdio.h>
#include <stdlib.h>

int a[] = {1,3,5,7,8,10,11,12,15,19,21,22,24,25,26};
int b[] = {2,4,5,6,9,16,17,18,27,30,31};

struct list {
        struct list *next;
        int v;
};

void merge(struct list *iter, struct list *base)
{
        struct list *last = iter;

        if (!iter) {
                return;
        }
        iter = iter->next;

        while (iter && (!base || iter->v < base->v)) {
                last = iter;
                iter = iter->next;
        }
        last->next = base;
        merge(base, iter);
}

int main(int argc, char **argv)
{
        int i = 0, j = 0;
        struct list *al = (struct list*)calloc(15, sizeof(*al));
        struct list *bl = (struct list*)calloc(11, sizeof(*bl));
        struct list *itera;
        struct list *iterb;

        // create 2 lists
        {
                for (i = 0; i < 15; i++) {
                        itera = &al[i];
                        itera->v = a[i];
                        itera->next = &al[i+1];
                }
                itera->next = NULL;

                for (i = 0; i < 11; i++) {
                        iterb = &bl[i];
                        iterb->v = b[i];
                        iterb->next = &bl[i+1];
                }
                iterb->next = NULL;
        }

        // merge 2 lists
        {
                merge(al, bl);
        }

        // print the result
        {
                for (; al; al=al->next) {
                        printf("%d,", al->v);
                }
				printf("\b \n");
        }
}
