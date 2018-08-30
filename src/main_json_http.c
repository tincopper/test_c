//
// Created by root on 18-8-29.
//
#include <stdio.h>
#include "cJSON.h"
#include "host_info.h"
#include "http_util.h"

int main() {

    cJSON *json = cJSON_CreateObject();
    //添加一个数字
    cJSON_AddNumberToObject(json, "ii", 5);
    cJSON_AddNumberToObject(json, "ht", current_system_time_millis());

    //将json结构格式化到缓冲区
    char *bufJson = cJSON_Print(json);
    printf("request body : \n%s\n\n", bufJson);

    char *url = "http://10.40.6.114:12800/instance/heartbeat";
    char resp[512];
    post_request(url, bufJson, resp);

    printf("response body:\n %s\n", resp);

    return 0;
}