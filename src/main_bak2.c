#include <stdio.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <time.h>
#include <sys/time.h>
#include <id_generator_util.h>
#include <sys/ioctl.h>
#include "cJSON.h"
#include "host_info.h"

/**
 * Create random UUID
 *
 * @param buf - buffer to be filled with the uuid string
 */
char *random_uuid(char buf[37]) {
    const char *c = "89ab";
    char *p = buf;
    int n;
    for (n = 0; n < 16; ++n) {
        int b = rand() % 255;
        switch (n) {
            case 6:
                sprintf(p, "4%x", b % 15);
                break;
            case 8:
                sprintf(p, "%c%x", c[rand() % strlen(c)], b % 15);
                break;
            default:
                sprintf(p, "%02x", b);
                break;
        }

        p += 2;
        switch (n) {
            case 3:
            case 5:
            case 7:
            case 9:
                *p++ = '-';
                break;
        }
    }
    *p = 0;
    return buf;
}


int main() {

    //------
    char *mac = current_host_mac();
    printf("current host mac address is : %s\n", mac);

    //------
    LONG i = current_system_time_millis();
    printf("currnet system time millis : %lld\n", i);

    //------
    int pid = current_thread_pid();
    printf("current thread pid : %d\n", pid);

    //------
    int ppid = current_parent_thread_pid();
    printf("current parent thread pid : %d\n", ppid);

    //------
    char *hostname = current_host_name();
    printf("hostname = %s\n", hostname);

    //------
    long hostid = current_host_id();
    printf("hostid = %ld\n", hostid);

    //------
    struct utsname buf = current_host_info();
    printf("sysname:%s\n", buf.sysname);
    printf("nodename:%s\n", buf.nodename);
    printf("release:%s\n", buf.release);
    printf("version:%s\n", buf.version);
    printf("machine:%s\n", buf.machine);

    char *name = current_os_name();
    printf("sysname:%s\n", name);

    //------
    char **currentIpv4 = current_ipv4();
    int len = sizeof(currentIpv4) / sizeof(currentIpv4[0]);
    //printf("len : %d\n", len);
    //printf("本机IP：%s\n", currentIpv4[0]);
    for (int i = 0; i < len; i++) {
        printf("本机IP：%s\n", currentIpv4[i]);
    }

    //------
    char *test[] = {"aaa", "bb", "cc", "ddddd", "eeee", "ffffff"};
    //二维数组的长度，就是求行的大小
    int length = sizeof(test) / sizeof(test[0]); //5
    printf("数组的长度为: %d\n", length);

    static char *strarray[4] = {};
    strarray[0] = "1";
    strarray[1] = "2";
    strarray[2] = "3";

    int strlen = sizeof(strarray) / sizeof(strarray[0]);
    printf("数组的长度为: %d\n", strlen);

    for (int i = 0; i < strlen; i++) {
        printf("数组的内容：%d,%s\n", i, strarray[i]);
    }

    //------ cjson库练习
    cJSON *json = cJSON_CreateObject();
    //向文档中增加一个键值对{"name":"tomgs"}
    cJSON_AddItemToObject(json, "name", cJSON_CreateString("tomgs")); // {"name":"tomgs"}
    //或者
    cJSON_AddStringToObject(json, "name_1", "tomgs_1");
    //添加一个数字
    cJSON_AddItemToObject(json, "age", cJSON_CreateNumber(18));
    //或者
    cJSON_AddNumberToObject(json, "age_1", 18);

    //添加一个数组
    cJSON *array = NULL;
    cJSON_AddItemToObject(json, "array", array = cJSON_CreateArray());
    cJSON_AddItemToArray(array, cJSON_CreateString("LOL"));
    cJSON_AddItemToArray(array, cJSON_CreateString("NBA"));
    cJSON_AddItemToArray(array, cJSON_CreateString("Go shopping"));
    //cJSON_AddStringToObject(array, "WWWW");

    //嵌套json
    cJSON *json1 = cJSON_CreateObject();
    cJSON_AddStringToObject(json1, "worker1", "programer");

    cJSON_AddItemToObject(json, "worker", json1);

    //将json结构格式化到缓冲区
    char *bufJson = cJSON_Print(json);
    printf("%s\n", bufJson);

    //------ hostinfo
    cJSON *instanceSpan = cJSON_CreateObject();
    cJSON_AddNumberToObject(instanceSpan, "ai", -1);

    char *agentUUId[] = {};
    rand64hex(agentUUId);
    cJSON_AddStringToObject(instanceSpan, "au", agentUUId[0]);
    cJSON_AddNumberToObject(instanceSpan, "rt", current_system_time_millis());

    cJSON *osInfo = cJSON_CreateObject();
    cJSON_AddStringToObject(osInfo, "osName", current_os_name());
    cJSON_AddStringToObject(osInfo, "hostname", current_host_name());
    cJSON_AddNumberToObject(osInfo, "processNo", current_thread_pid());
    //cJSON_AddItemToObject(osInfo, "ipv4s", cJSON_CreateStringArray(current_ipv4(), sizeof(currentIpv4) / sizeof(currentIpv4[0])));

    cJSON *ipv4s = NULL;
    cJSON_AddItemToObject(osInfo, "ipv4s", ipv4s = cJSON_CreateArray());

    char **ipv4 = current_ipv4();
    int l = sizeof(currentIpv4) / sizeof(currentIpv4[0]);
    for (int i = 0; i < l; i++) {
        char *string = ipv4[i];
        char result1[64] = "";
        strcpy(result1, string);
        cJSON_AddItemToArray(ipv4s, cJSON_CreateString(result1));
    }

    cJSON_AddItemToObject(instanceSpan, "oi", osInfo);

    //将json结构格式化到缓冲区
    char *result = cJSON_Print(instanceSpan);
    printf("%s\n", result);

    //------ uuid
    char guid[37];
    random_uuid(guid);
    printf("guid = %s\n", guid);
    random_uuid(guid);
    printf("guid = %s\n", guid);

    //libuuid
    /*uuid_t uuid;
    char str[36];
    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    printf("%s\n", str);*/

    char *uuid[] = {};
    rand64hex(uuid);
    printf("%s\n", uuid[0]);
    
    // -------
    char *s1 = "123456";
    char *s2 = "xx";
    char *re = strstr(s1, s2);

    int ii = 123;
    //char *str_i = (char *)ii;
    char str_i[64];
    //sscanf(&ii, "%s", str_i);
    sprintf(str_i, "%d", ii);
    printf("------> str_i: %s\n", str_i);

    // ---------
    char *url = "http:\/\/www.baidu.com";
    char host[64];
    sscanf(url, "http://%s", host);
    printf("-----> host: %s", host);

    // ------
    int num = 123;
    char *str01 = "xxx";
    char *str02 = "yyy";
    char res[64];
    sprintf(res, "%d/%s/%s", num, str01, str02);
    printf("------> res: %s\n", res);

    // ------
    long long int millis = host_time_millis();
    long long int usec = host_time_usec();
    long long int ms = usec / 1000LL;

    printf("------> millis : %lld, usec: %lld, ms: %lld", millis, usec, ms);
    
    return 0;
}