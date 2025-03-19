#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_b, pid_c, pid_d;
    printf("A: pid = %d, ppid = %d\n", getpid(), getppid());

    pid_b = fork();
    if (pid_b == 0) {
        // B 进程
        printf("B: pid = %d, ppid = %d\n", getpid(), getppid());

        pid_c = fork();
        if (pid_c == 0) {
            // C 进程
            printf("C: pid = %d, ppid = %d\n", getpid(), getppid());

            pid_d = fork();
            if (pid_d == 0) {
                // D 进程
                printf("D: pid = %d, ppid = %d\n", getpid(), getppid());
            } else {
                wait(NULL); // C 等待 D
            }
        } else {
            wait(NULL); // B 等待 C
        }
    } else {
        wait(NULL); // A 等待 B
    }

    return 0;
}