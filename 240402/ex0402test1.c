#include <stdio.h>
#include <sys/stat.h>

int isDirectoryExists(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) {
        return 0;
    }
    return S_ISDIR(info.st_mode);
}

int main() {
    const char *path = "test";
    if (isDirectoryExists(path)) {
        printf("Directory exists.\n");
    } else {
        printf("Directory does not exist.\n");
    }
    return 0;
}

