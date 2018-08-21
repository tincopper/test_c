//
// Created by tomgs on 18-8-13.
//

#include <stdio.h>
#include "load_balance.h"

int main()
{
    int i = 0;
    int weights[] = {4, 2, 1};
    char *names[] = {"a", "b", "c"};
    int size = sizeof(weights) / sizeof(int);

    server *ss = initServers(names, weights, size);

    printf("server is ");
    for (i = 0; i < size; i++) {
        printf("%s(%d) ", ss[i].name, ss[i].weight);
    }
    printf("\n");

    printf("\nwrr_nginx sequence is ");
    wrr_nginx(ss, weights, size);

    char *str = "123456789";
    char tmp[128];
    strncpy(tmp, str, 3);
    str = tmp;
    printf("\n%s\n%s", str, tmp);

    return 0;
}