#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程
        printf("子进程: pid = %d，后台执行 test1\n", getpid());

        // 后台执行 test1 可执行文件
        execl("./test1", "./test1", NULL);

        // 如果 execl 失败
        perror("execl 失败");
    } else if (pid > 0) {
        // 主进程
        printf("主进程: pid = %d，继续执行主进程逻辑\n", getpid());
    } else {
        perror("fork 失败");
    }

    return 0;
}