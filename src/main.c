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

    /*char *url = "http://wwww.baidu.com?a=b&c=d";
    char *tmp;
    int len;

    char *p = strchr(url, '?');

    printf("%s\n", p);
    printf("%s\n", (char *)(p - url));
    snprintf(tmp, len, "%s", url);
    printf("%s\n", tmp);*/


    //char *s = "0123456789012345678901234567890";
    char *s = "http://wwww.baidu.com?a=b&c=d";
    char *p, *q;
    //unsigned char tmp;
    p = strchr(s, '?');
    printf("原来的字符串:%s\n", s);
    printf("5之后的字符串:%s\n", p);

    unsigned char tmp = (unsigned char)(strchr(s, '?') - s);
    q = (tmp > 0) ? strndup(s, tmp) : strdup(s);
    printf("5之前的字符串:%s\n", q);

    for (;;);
}