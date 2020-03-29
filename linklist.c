#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "linklist.h"

#define count 100 // for average
#define round 500 // for size

int main()
{
    int i, j, input;
    long long ts[round], tm[round];
    struct timespec start, stop;
    FILE *fp;
    if(!(fp = fopen("time.txt","w"))) {
        printf("Open file error\n");
        return -1;
    }
    for(j = 0; j < round; j++) {
        ts[j] = 0;
        tm[j] = 0;
    }
    for(j = 0; j < round; j++) {
       for(i = 0; i < count; i++) {
        struct __list *a = malloc(sizeof(struct __list));
        struct __list *b = malloc(sizeof(struct __list));
        a = NULL;
        b = NULL;
        
        for(int k = 0; k < j; k++) {
            input = rand();
            insert_node(&a, input);
            insert_node(&b, input);
        }

            clock_gettime(CLOCK_MONOTONIC, &start);
            a = sort(a);
            clock_gettime(CLOCK_MONOTONIC, &stop);
            ts[j] += stop.tv_nsec - start.tv_nsec;
            if (ts[j] < 0 && j > 0)
                ts[j] = ts[j - 1];
            delete_list(a);

            printf("\n%dnd sorting-->\n",j);
//        print_list(b);
            clock_gettime(CLOCK_MONOTONIC, &start);
            b = merge_sort(b, j + 1);
            clock_gettime(CLOCK_MONOTONIC, &stop);
//            printf("%dn\t sorted\n", i + 1);
            tm[j] += stop.tv_nsec - start.tv_nsec;
//            print_list(b);
            if (tm[j] < 0 && j > 0)
//                tm[j] = tm[j - 1];
            delete_list(b); 
        }
        ts[j] /= count;
        tm[j] /= count;
        fprintf(fp,"%d\t%lld\t%lld\n", j+1, ts[j], tm[j]    );
//        printf("%d\t%ld\n", j+1, ts);
    }
    fclose(fp);
}
