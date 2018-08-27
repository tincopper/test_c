//
// Created by root on 18-8-22.
//
#include <stdio.h>
#include "cJSON.h"
#include "host_info.h"

int main()
{
    cJSON *json = cJSON_CreateObject();
    //添加一个数字
    cJSON_AddNumberToObject(json, "ii", 5);
    cJSON_AddNumberToObject(json, "ht", host_time_millis());

    //将json结构格式化到缓冲区
    char *bufJson = cJSON_Print(json);
    printf("%s\n", bufJson);

    return 0;
}