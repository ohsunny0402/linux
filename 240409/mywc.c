#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_BUF_SIZE 1024

void count(const char *filename);

int main(int argc, char *argv[]) {

    pid_t pid[3];

    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            perror("fork");
            return 1;
        } else if (pid[i] == 0) {
            count(argv[i + 1]);
            return 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}

void count(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    int char_count = 0, word_count = 0, line_count = 0;
    char buffer[MAX_BUF_SIZE];

    while (fgets(buffer, MAX_BUF_SIZE, file) != NULL) {
        line_count++;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t') {
                char_count++;
            }
            if ((buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') &&
                (buffer[i - 1] != ' ' && buffer[i - 1] != '\n' && buffer[i - 1] != '\t')) {
                word_count++;
            }
        }
    }

    if (char_count > 0) {
        word_count++;
    }

    printf("Lines: %d, Words: %d, Char: %d\n", line_count, word_count, char_count);

    fclose(file);
}

