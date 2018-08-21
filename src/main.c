//
// Created by tincopper on 18-8-21.
//
#include <stdio.h>
#include <pthread.h>

void thread(void) {
    int i;
    for (i=0; i < 3; i++) {
        printf("This is a pthread.\n");
    }
}

int main() {

    /**
     * 多线程编程测试
     */
    pthread_t id;
    int i, ret;
    ret = pthread_create(&id, NULL, (void *) thread, NULL); // 成功返回0，错误返回错>误编号
    if (ret != 0) {
        printf("Create pthread error!\n");
        exit(1);
    }
    for (i=0; i<3; i++)
        printf("This is the main process.\n");

    pthread_join(id, NULL);

    return 0;
}