//
// Created by root on 18-8-13.
//

#ifndef TEST_C_LOAD_BALANCE_H
#define TEST_C_LOAD_BALANCE_H

typedef struct
{
    int weight;
    int cur_weight;
    char name[3];
} server;

server *initServers(char **names, int *weights, int size);

int getNextServerIndex(server *ss, int size);

void wrr_nginx(server *ss, int *weights, int size);

#endif //TEST_C_LOAD_BALANCE_H
