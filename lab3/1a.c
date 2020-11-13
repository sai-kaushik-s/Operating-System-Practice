// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Main driver function for the program
int main(){
    // Create a new process
    pid_t pid = fork();
    // If the fork failed
    if(pid < 0) printf("Fork failed.\n");
    // Child process: Executes the command ls using execl
    else if(pid == 0) execl("/bin/ls", "ls", NULL);
    // Parent process
    else {
        printf("Parent process.\n");
        // Wait for the child to complete
        wait(NULL);
        printf("Parent waited for completion of child process.\n");
    }
    exit(0);
}