#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MSGSIZE 16

void onerror(char *msg) {
    printf("%s", msg);
    exit(1);
}

int main() {
    int p1[2], p2[2], p3[2];
    char msg[MSGSIZE];
    int i;
    pid_t pid1, pid2, pid3;
    fd_set initset, newset;

    pid1 = pid2 = pid3 = 0;

    if(pipe(p1) == -1)
        onerror("fail to call pipe() #1\n");
    if(pipe(p2) == -1)
        onerror("fail to call pipe() #2\n");
    if(pipe(p3) == -1)
        onerror("fail to call pipe() #3\n");
    if((pid1 = fork()) == -1)
        onerror("fail to call fork() #1\n");
    if(pid1 > 0)
        if((pid2 = fork()) == -1)
            onerror("fail to call fork() #2\n");
    if(pid1 > 0 && pid2 > 0)
        if((pid3 = fork()) == -1)
            onerror("fail to call fork() #3\n");

    if(pid1 > 0 && pid2 > 0 && pid3 > 0) {
        printf("parent: %d\n", getpid());
        close(p1[1]); close(p2[1]); close(p3[1]);

        FD_ZERO(&initset);
        FD_SET(p1[0], &initset);
        FD_SET(p2[0], &initset);
        FD_SET(p3[0], &initset);

        newset = initset;
        while(select(p3[0] + 1, &newset, NULL, NULL, NULL) > 0) {
            if(FD_ISSET(p1[0], &newset))
                if(read(p1[0], msg, MSGSIZE) > 0)
                    printf("[parent] I am child1 from child1\n");
            if(FD_ISSET(p2[0], &newset))
                if(read(p2[0], msg, MSGSIZE) > 0)
                    printf("[parent] I am child2 from child2\n");
            if(FD_ISSET(p3[0], &newset))
                if(read(p3[0], msg, MSGSIZE) > 0)
                    printf("[parent] I am child3 from child3\n");
            newset = initset;
        }
    }
    else if(pid1 == 0 && pid2 == 0 && pid3 == 0) {
        printf("child1: %d\n", getpid());
        close(p1[0]); close(p2[0]); close(p2[1]); close(p3[0]); close(p3[1]);

        for(i = 0; i < 3; i++) {
            sleep(i + 1);
            printf("child1: send message %d\n", i);
            write(p1[1], "i'm child1", MSGSIZE);
        }
        printf("child1: bye!\n");
        exit(0);
    }
    else if(pid1 > 0 && pid2 == 0 && pid3 == 0) {
        printf("child2: %d\n", getpid());
        close(p1[0]); close(p1[1]); close(p2[0]); close(p3[0]); close(p3[1]);

        sleep(3);
        printf("child2: send message %d\n", i);
        write(p2[1], "i'm child2", MSGSIZE);
        
	sleep(0);
        printf("child2: send message %d\n", i);
	write(p2[1], "i'm child2", MSGSIZE);
	
	sleep(1);
        printf("child2: send message %d\n", i);
        write(p2[1], "i'm child2", MSGSIZE);

	printf("child2: bye!\n");
        exit(0);
    }
    else if(pid1 > 0 && pid2 > 0 && pid3 == 0) {
        printf("child3: %d\n", getpid());
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]); close(p3[0]);
    
	sleep(4);
        printf("child3: send message %d\n", i);
        write(p3[1], "i'm child3", MSGSIZE);
	    
	sleep(5);
        printf("child3: send message %d\n", i);
        write(p3[1], "i'm child3", MSGSIZE);
	
	sleep(6);
        printf("child3: send message %d\n", i);
        write(p3[1], "i'm child3", MSGSIZE);

        printf("child3: bye!\n");
        exit(0);
    }
}

