//
// Created by root on 18-8-22.
//
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "host_info.h"

int count = 0;
void signal_handler(int signal)
{
    count ++;
    printf("count : %d, %d\n", count, signal);
}

int main()
{
    set_timer(1, signal_handler);

    for (;;);
}