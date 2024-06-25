#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

int main() {
    const char *path = "test";
    DIR *dirp;
    struct dirent *dentry;
    int fileCount = 0;
    int diCount = 0;
    
    if ((dirp = opendir(path)) == NULL) {
        fprintf(stderr, "Failed to open\n");
        return 1;
    }

    while ((dentry = readdir(dirp)) != NULL) {
        if (strcmp(dentry->d_name, ".") == 0 || strcmp(dentry->d_name, "..") == 0) {
            continue;
        }

        if (dentry->d_type == DT_REG) {
            fileCount++;
        } else if (dentry->d_type == DT_DIR) {
            diCount++;
        }
    }

    closedir(dirp);

    printf("File count: %d\n", fileCount);
    printf("Directory count: %d\n", diCount);

    return 0;
}

