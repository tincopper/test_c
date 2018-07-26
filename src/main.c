#include <stdio.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "cJSON.h"
#include "host_info.h"

int main() {

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
    if (gethostname(hostname, strlen(hostname)) < 0) {
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
        printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    }

}