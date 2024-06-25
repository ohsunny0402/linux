#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

void write_time() {
    time_t t = time(NULL);
    char *buf = ctime(&t);
    int fd = open("curtime.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error open tlqkf");
        exit(1);
    }
    write(fd, buf, strlen(buf));

}

void handler(int signum) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    signal(SIGCHLD, handler);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed tlqkf");
        exit(1);
    }
     else if (pid == 0) {
        if (setsid() == -1) {
            perror("setsid");
            exit(1);
        }
        signal(SIGHUP, SIG_IGN);
        while (1) {
            write_time();
            sleep(10);
        }
    }

    return 0;
}
