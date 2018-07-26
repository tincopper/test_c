//
// Created by tangzy on 18-7-26.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

//获取地址
//返回IP地址字符串
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