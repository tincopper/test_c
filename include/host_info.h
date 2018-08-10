//
// Created by tangzy on 18-7-26.
//

#define LONG long long
#define INT long int

#define MO_USEC_PER_SEC         1000000l

/**
 * 获取当期系统时间毫秒数
 * @return 时间毫秒数
 */
LONG current_system_time_millis();

/**
 * 获取当前运行线程的pid
 * @return pid
 */
int current_thread_pid();

/**
 * 获取当期运行线程的父线程pid
 * @return parent pid
 */
int current_parent_thread_pid();

/**
 * 获取当期系统的主机名
 * @return hostname
 */
char *current_host_name();

/**
 * 获取当期系统的主机id
 * @return hostid
 */
long current_host_id();

/**
 * 返回系统当期的常规信息
 * @return host_info
 */
struct utsname current_host_info();

/**
 * 获取当前系统的OS名称
 * @return
 */
char *current_os_name();

/**
 * 获取当前系统的ipv4地址
 * @return string[]
 */
char **current_ipv4();

/**
 * 获取当前系统的ipv6地址
 * @return
 */
char *current_ipv6();

/**
 * 获取当前系统的mac地址
 * @return 如果错误返回NULL,否则返回字符串
 */
char *current_host_mac();

static inline long long host_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    /**
     * int ：表示数据范围在-32768到32767之间
     * long int : 表示的范围在-2147483648到2147483647之间
     * long long : 表示的范围在-9223372036854775808 到 9223372036854775807之间
     *
     * 毫秒有13位超过了long int范围，所需要转为long long类型
     */
    long long t_sec = (long long)tv.tv_sec;
    long long t_usec = (long long)tv.tv_usec;
    return (t_sec * 1000000LL + t_usec) / 1000LL;
}

static inline long long host_time_usec()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (long long) tv.tv_sec * MO_USEC_PER_SEC + (long long) tv.tv_usec;
}
