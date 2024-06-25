#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int x, y;

     do {
        printf("(x,y) (x < y, 1 <= x,y <= 10): ");
        scanf("%d %d", &x, &y);
        
        if (x >= y || x < 1 || y > 10) {
            printf("re write.\n");
        }
    } 
    while (x >= y || x < 1 || y > 10);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "failed.\n");
        return 1;
    } else if (pid == 0) {
        int sum = 0;
        for (int i = x; i <= y; i++) {
            sum += i;
        }
        printf("child result: %d\n", sum);
    } else {
        int result_pow = 1;
        for (int i = 0; i < y; i++) {
            result_pow *= x;
        }
        printf("parent result: %d\n", result_pow);
        
        wait(NULL);

        printf("parent add: %d\n", result_pow + ((y - x + 1) * (x + y) / 2));
    }

    return 0;
}

