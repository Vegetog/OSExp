#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_b, pid_c, pid_d, pid_e, pid_f;

    printf("A: pid = %d, ppid = %d\n", getpid(), getppid());

    pid_b = fork();
    if (pid_b == 0) {
        // B 进程
        printf("B: pid = %d, ppid = %d\n", getpid(), getppid());

        pid_d = fork();
        if (pid_d == 0) {
            // D 进程
            printf("D: pid = %d, ppid = %d\n", getpid(), getppid());
        } else {
            wait(NULL); // B 等待 D
        }

    } else {
        pid_c = fork();
        if (pid_c == 0) {
            // C 进程
            printf("C: pid = %d, ppid = %d\n", getpid(), getppid());

            pid_e = fork();
            if (pid_e == 0) {
                // E 进程
                printf("E: pid = %d, ppid = %d\n", getpid(), getppid());
            } else {
                pid_f = fork();
                if (pid_f == 0) {
                    // F 进程
                    printf("F: pid = %d, ppid = %d\n", getpid(), getppid());
                } else {
                    wait(NULL); // C 等待 F
                    wait(NULL); // C 等待 E
                }
            }
        } else {
            wait(NULL); // A 等待 C
            wait(NULL); // A 等待 B
        }
    }

    return 0;
}