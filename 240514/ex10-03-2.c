#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int num = 0;

int main() {
    static struct sigaction act;
    void int_handle(int);

    act.sa_handler = int_handle;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);

    while (1) {
        printf("i`m sleepy...\n");
        sleep(1);
        if (num >= 1) {
            exit(0);
        }
    }
}

void int_handle(int signum) {
    printf("SIGINT: %d\n", signum);
    printf("int_handle called %d times\n", ++num);

    int fd = open("a.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (write(fd, "Goodbye!\n", 9) == -1) {
        perror("write");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
}

