#include <stdio.h>
#include <sys/stat.h>

int softlink(const char *path) {
    struct stat info;
    if (lstat(path, &info) != 0) {
        return -1;
    }
    return S_ISLNK(info.st_mode);
}

int main() {
    const char *path = "test"; 
    int result = softlink(path);
    if (result == -1) {
        printf("call failed\n");
    } else if (result) {
        printf("soft link.\n");
    } else {
        printf("not soft link.\n");
    }
    return 0;
}

