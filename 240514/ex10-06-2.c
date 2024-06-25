#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int count = 5;

    if((pid = fork()) > 0){
        sleep(2);
        kill(pid, SIGINT);
        waitpid(pid, NULL, 0);
        printf("[parent] bye!\n");
        exit(0);
    }
    else if(pid == 0){

        while(count){
		printf("[child] count is %d\n", count--);
		sleep(1);
	}

	kill(getppid(), SIGCHLD);
	printf("[child] bye!\n");
	exit(0);
    }
    else{
        printf("fall to fork\n");
    }

    return 0;
}

