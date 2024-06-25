#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>
 
int main(int argc, char *argv[]){
 
        DIR *dirp;
        struct  dlrent *dentry;
 
        if ((dirp = opendir("."))== NULL){
                exit(1);
        }
	printf("file is okay.. \n");
        while(dentry = readdir(dirp)){
                if(dentry->d_ino!=0)
                        printf("%s\n", dentry->d_name);
        }

	rewinddir(dirp);
	printf("remove file..\n");
	while(dentry = readdir(dirp)){
		if(dentry = readdir(dirp)){
			printf("%s\n", dentry->d_name);
		}
	}
         closedir(dirp);
}

