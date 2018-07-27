#include <stdio.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <time.h>
#include <sys/time.h>
#include "cJSON.h"
#include "host_info.h"

int main() {

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

    //------
    current_ipv4();

    //------
    char *test[] = {"aaa", "bb", "cc", "ddddd", "eeee", "ffffff"};
    //二维数组的长度，就是求行的大小
    int length = sizeof(test) / sizeof(test[0]); //5
    printf("数组的长度为: %d\n", length);

    /*char *strarray[3];
    *strarray[0] = "1";
    *strarray[1] = "2";
    *strarray[2] = "3";

    int strlen = sizeof(*strarray) / sizeof(char);
    printf("数组的长度为: %d\n", strlen);*/
    /*for () {

    }*/


    return 0;
}