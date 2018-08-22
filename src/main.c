//
// Created by root on 18-8-22.
//
#include <stdio.h>
#include "load_balance.h"

int main()
{
    int i = 0;
    //char *names[] = {"a", "b", "c"};
    char *names[] = {"a"};
    int size = sizeof(names) / sizeof(names[0]);

    server *ss = initDefaultServers(names, size);

    printf("server is ");
    for (i = 0; i < size; i++) {
        printf("%s(%d) ", ss[i].name, ss[i].weight);
    }
    printf("\n");

    printf("\nwrr_nginx sequence is : \n");
    //wrr_nginx(ss, weights, size);

    int sum = 10;
    for (i = 0; i < sum; i++)
    {
        int index = getNextServerIndex(ss, size);
        printf("%s(%d)\n", ss[index].name, ss[index].weight);
    }

    //测试动态创建数组
    char **strs;
    strs = malloc(sizeof(char));
    for (int i = 0; i < 3; i++) {
        strs[i] = "abcde";
    }

    for (int i = 0; i < 3; i++) {
        printf("%s\n", strs[i]);
    }

    return 0;
}