
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
 
int main (int argc, char *argv[]) {
    char pid[16];
 
    snprintf(pid, sizeof(pid), "%i", 0);//getpid());
    if (argc != 2)
        return 0;

    printf("%s=%s",argv[1], crypt(pid, "$1$awesome"));
 
    if (strcmp(argv[1], crypt(pid, "$1$awesome")) == 0) {
        printf("WIN!\n");
        system("/bin/bash -p");
    } else {
        printf("phail... :/\n");
    }
    return 0;
}
