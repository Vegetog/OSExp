#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char input[100];

    // 创建管道
    if (pipe(fd) == -1) {
        perror("pipe 创建失败");
        exit(1);
    }

    printf("主进程输入字符串: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // 去除换行符

    pid_t sender_pid = fork();
    if (sender_pid == 0) {
        // 发送进程
        close(fd[0]); // 关闭读端
        write(fd[1], input, strlen(input) + 1);
        printf("发送进程: 已发送 \"%s\"\n", input);
        close(fd[1]); // 关闭写端
        _exit(0);
    }

    // 主进程等待发送进程结束
    waitpid(sender_pid, NULL, 0);

    pid_t receiver_pid = fork();
    if (receiver_pid == 0) {
        // 接收进程
        char buffer[100];
        close(fd[1]); // 关闭写端
        read(fd[0], buffer, sizeof(buffer));
        close(fd[0]); // 关闭读端
        printf("接收进程: 收到 \"%s\"\n", buffer);

        // 传递 buffer 给 encrypt 程序，后台执行
        execl("./encrypt", "./encrypt", buffer, NULL);
        perror("execl 启动 encrypt 失败");
        _exit(1);
    }

    // 主进程等待接收进程结束
    waitpid(receiver_pid, NULL, 0);

    return 0;
}