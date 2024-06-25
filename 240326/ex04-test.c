#include <stdio.h>
#include <unistd.h>

int main() {
    char *filename = "b.txt";

    if (access(filename, F_OK) != -1) {
        printf("%s file is okay.\n", filename);
    } else {
        printf("%s file is not.\n", filename);
    }

    return 0;
}

