#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num;
    printf("parent: number: ");
    scanf("%d", &num);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork fail\n");
        return 1;
    } else if (pid == 0) {
 
        printf("child: 1 ~ %d all * ", num);
        int result = 1;
        for (int i = 1; i <= num; i++) {
            result *= i;
        }
        printf("= %d \n", result);
    } else {
        int sum = 0;
        for (int i = 1; i <= num; i++) {
            sum += i;
        }
        printf("parent: 1 ~ %d all + =  %d\n", num, sum);
    }

    return 0;
}

