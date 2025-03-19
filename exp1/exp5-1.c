#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int count = 0; // 用于统计子进程数量

void create_process() {
    pid_t pid;

    // 创建 B
    pid = vfork();
    if (pid == 0) {
        count++;
        printf("B: pid = %d, ppid = %d\n", getpid(), getppid());

        // 创建 C
        pid = vfork();
        if (pid == 0) {
            count++;
            printf("C: pid = %d, ppid = %d\n", getpid(), getppid());

            // 创建 D
            pid = vfork();
            if (pid == 0) {
                count++;
                printf("D: pid = %d, ppid = %d\n", getpid(), getppid());

                _exit(0); // vfork 必须使用 _exit 立即结束
            } else {
                _exit(0);
            }
        } else {
            _exit(0);
        }
    }
}

int main() {
    printf("A (主进程): pid = %d, ppid = %d\n", getpid(), getppid());

    create_process();
    // 主进程等待所有子进程结束
    while (wait(NULL) > 0);

    printf("主进程统计的子进程数量: %d\n", count);

    return 0;
}