//
// Created by tangzy on 18-7-27.
//

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
#include <bits/ioctls.h>
#include <sys/ioctl.h>
#include "cJSON.h"
#include "host_info.h"

/**
 * 备份main.c内容
 */
void bak_main() {
    /**
     * getpid():获取当期运行的进程PID
     * getppid(): 获取父进程的PID
     */
    printf("pid = %d, ppid = %x\n", getpid(), getppid());

    /**
     * gethostname():获取主机名
     * gethostid(): 获取主机ID
     */
    char hostname[128];
    long hostid;
    if (gethostname(hostname, sizeof(hostname)) < 0) {
        perror("gethostname");
        exit(1);
    }
    printf("hostname = %s\n", hostname);
    if ((hostid = gethostid()) < 0) {
        perror("gethostid");
        exit(1);
    }
    printf("hostid = %ld\n", hostid);

    /**
      * 获取系统信息
      */
    struct utsname buf;
    if (uname(&buf)) {
        perror("uname");
        exit(1);
    }
    printf("sysname:%s\n", buf.sysname);
    printf("nodename:%s\n", buf.nodename);
    printf("release:%s\n", buf.release);
    printf("version:%s\n", buf.version);
    printf("machine:%s\n", buf.machine);

    /**
     * 获取本机ipv4
     */
    struct hostent *hent;
    char hname[128];
    gethostname(hname, sizeof(hname));
    hent = gethostbyname(hname);
    printf("hostname: %s/naddress list: ", hent->h_name);
    for(int i = 0; hent->h_addr_list[i]; i++) {
        printf("%s/t\n", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    }

    /**
     * 获取IP地址信息
     */
    struct ifaddrs *addrs;
    void *tmpAddrPtr = NULL;
    if (getifaddrs(&addrs)) {
        perror("getifaddrs");
        exit(1);
    }
    //char *name = addrs->ifa_name;
    //printf("netcard name : %s", name);
    while (addrs != NULL) {
        if (addrs->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *)addrs->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IPv4 Address %s\n", addrs->ifa_name, addressBuffer);
        } else if (addrs->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr = &((struct sockaddr_in *)addrs->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IPv6 Address %s\n", addrs->ifa_name, addressBuffer);
        }
        addrs = addrs->ifa_next;
    }

    /**
     * 获取时间
     */
    time_t *timep = malloc(sizeof(*timep));
    time(timep); //获取秒数
    printf("%ld\n", timep);
    char *s = ctime(timep); //转换成可读的时间格式
    printf("%s\n", s);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    /**
     * int ：表示数据范围在-32768到32767之间
     * long int : 表示的范围在-2147483648到2147483647之间
     * long long : 表示的范围在-9223372036854775808 到 9223372036854775807之间
     */
    long long time = (long long)tv.tv_sec;
    printf("second:%ld\n", tv.tv_sec);  //秒
    printf("usec : %ld\n", tv.tv_usec);
    printf("millisecond:%lld\n", time * 1000LL + time / 1000LL);  //毫秒有15位超过了long int范围，所需要转为long long类型
    printf("microsecond:%lld\n", time*1000000LL + time);  //微秒

}

/**
 * 这个方法不可用
 * //获取地址
 * //返回IP地址字符串
 * @param outip
 * @return
 * @deprecated
 */

int getlocalip(char *outip) {
    int i = 0;
    int sockfd;
    struct ifconf ifconf;
    char buf = (char) malloc(512);
    struct ifreq *ifreq;
    char *ip;

    //初始化ifconf
    ifconf.ifc_len = 512;
    ifconf.ifc_buf = buf;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf); //获取所有接口信息
    close(sockfd);
    //接下来一个一个的获取IP地址
    ifreq = (struct ifreq *) buf;
    i = ifconf.ifc_len / sizeof(struct ifreq);
    char *pos = outip;
    int count;
    for (count = 0; (count < 5 && i > 0); i--) {
        ip = inet_ntoa(((struct sockaddr_in *) &(ifreq->ifr_addr))->sin_addr);

        if (strncmp(ip, "127.0.0.1", 3) == 0) //排除127.x.x.x，继续下一个
        {
            ifreq++;
            continue;
        } else {
            printf("%s\n", ip);
            strcpy(pos, ip);
            int len = strlen(ip);
            pos = '\t';
            pos += len + 1;
            count++;
            ifreq++;
        }
    }
    free(buf);
    return 0;
}