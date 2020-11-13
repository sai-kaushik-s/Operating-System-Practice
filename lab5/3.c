// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Function definitions
void subString(char* s, char* sub, int p, int n);
void printSubString(char* s, int n);

/// Main driver function
int main(){
    int WPRC[2], pid;
    char readMsg[1024], writeMsg[1024];
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
        read(WPRC[0], readMsg, sizeof(readMsg));
        printf("The substrings of %s: ", readMsg);
        printSubString(readMsg, strlen(readMsg));
    }
    else {
        printf("Enter a string: ");
        fgets(writeMsg, sizeof(readMsg), stdin);
        fflush(stdin);
        strcpy(writeMsg, strtok(writeMsg, "\n"));
        write(WPRC[1], writeMsg, sizeof(writeMsg));
    }
}

void subString(char* s, char* sub, int p, int n){
    int c = 0;
    while (c < n) {
        sub[c] = s[p+c];
        c++;
    }
    sub[c] = '\0';
}

void printSubString(char* s, int n){
    char c[1024];
    printf("{ ");
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= n - i; j++){
            subString(s, c, i, j);
            printf("%s, ", c);
        }
    }
    printf("\b\b }\n");
}