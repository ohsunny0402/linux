#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid[2];
    int status;

    for (int i = 0; i < 2; i++) {
        pid[i] = -1;
    }

    for (int i = 0; i < 2; i++) {
        pid[i] = fork();

        
        if (pid[i] > 0) {
            printf("Parent: Created child %d with PID %d\n", i + 1, pid[i]);
        } 
        
        else if (pid[i] == 0) {
            printf("Child %d: My PID is %d, My Parent's PID is %d\n", i + 1, getpid(), getppid());
            exit(0);
        } 
        
        else {
            printf("Failed to fork\n");
            exit(1);
        }
    }

    if (getpid() > 0) {
        for (int i = 0; i < 2; i++) {
            waitpid(pid[i], &status, 0);
            printf("Parent: Child %d with PID %d exited with status %d\n", i + 1, pid[i], status);
        }
    }

    return 0;
}

