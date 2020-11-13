#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
        printf("Child Process - Enter a string:\n");
        fgets(writeMsg, sizeof(readMsg), stdin);
        strcpy(writeMsg, strtok(writeMsg, "\n"));
        write(WCRP[1], writeMsg, sizeof(writeMsg));
        read(WPRC[0], readMsg, sizeof(readMsg));
        printf("concatenated string is: %s\n", readMsg);
    }
    else {
        close(WPRC[0]);
        close(WCRP[1]);
        printf("Parent Process - Enter a string:\n");
        fgets(writeMsg, sizeof(readMsg), stdin);
        strcpy(writeMsg, strtok(writeMsg, "\n"));
        read(WCRP[0], readMsg, sizeof(readMsg));
        strcpy(writeMsg, strcat(writeMsg, readMsg));
        write(WPRC[1], writeMsg, sizeof(writeMsg));
    }
}