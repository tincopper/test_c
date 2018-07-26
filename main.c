#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("Hello, World!\n");
    //get current app pid
    printf("pid = %d, ppid = %x\n", getpid(), getppid());
    return 0;
}