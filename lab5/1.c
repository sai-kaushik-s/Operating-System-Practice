#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *strrev(char *str);

int main(){
    int WCRP[2], WPRC[2], pid;
    char readMsg[1024], writeMsg[1024];
    if (pipe(WCRP) < 0){
        perror("Could not pipe.\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(WPRC) < 0){
        perror("Could not pipe.\n");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0) {
        perror("Could not fork.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        close(WCRP[0]);
        close(WPRC[1]);
        read(WPRC[0], readMsg, sizeof(readMsg));
        strcpy(writeMsg, strrev(readMsg));
        write(WCRP[1], writeMsg, sizeof(writeMsg));
    }
    else {
        close(WPRC[0]);
        close(WCRP[1]);
        printf("Enter a string: ");
        fgets(writeMsg, sizeof(readMsg), stdin);
        fflush(stdin);
        strcpy(writeMsg, strtok(writeMsg, "\n"));
        write(WPRC[1], writeMsg, sizeof(writeMsg));
        read(WCRP[0], readMsg, sizeof(readMsg));
        printf("The reversed string is: %s\n", readMsg);
    }
}

char *strrev(char *str){
    char *p1, *p2;
    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}