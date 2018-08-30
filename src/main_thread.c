//
// Created by tincopper on 18-8-21.
//
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h> // 包含setitimer()函数
#include <stdlib.h>
#include <signal.h>  //包含signal()函数

static int count = 0;
static struct itimerval oldtv;

typedef struct args {
    int id;
    char *name;
};

void set_timer()
{
    struct itimerval itv;
    itv.it_interval.tv_sec = 1;  //设置为1秒
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &itv, &oldtv);  //此函数为linux的api,不是c的标准库函数
}

void signal_handler(int m)
{
    count ++;
    printf("%d\n", count);
}

void thread() {
    int i;
    for (i=0; i < 3; i++) {
        printf("This is a pthread.\n");
    }
}

void thread1(struct args *arg) {
    printf("This is a pthread.  %s\n", arg->name);
    signal(SIGALRM, signal_handler);  //注册当接收到SIGALRM时会发生是么函数；
    set_timer();  //启动定时器
    for (;;);  //阻塞，等待时间执行
}


int main() {

    /**
     * 多线程编程测试
     */
    pthread_t id;
    int i, ret;

    char *str = "ssss";
    int num = 100;

    struct args args1;
    args1.id = num;
    args1.name = str;

    //ret = pthread_create(&id, NULL, (void *) thread, NULL); // 成功返回0，错误返回错>误编号
    //ret = pthread_create(&id, NULL, (void *) thread, str); // 成功返回0，错误返回错>误编号 ,传入一个参数
    ret = pthread_create(&id, NULL, (void *) thread1, &args1); // 传入多个参数，使用结构体

    if (ret != 0) {
        printf("Create pthread error!\n");
        exit(1);
    }

    sleep(1);

    for (i=0; i<3; i++) {
        printf("This is the main process.\n");
    }

    //pthread_join(id, NULL);

    for (;;);

    return 0;
}