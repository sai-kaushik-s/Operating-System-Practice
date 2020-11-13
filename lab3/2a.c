// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Main driver function for the program
int main(){
    // Scan the number of elements to be generated
    int n;
    printf("Enter the number of terms to be generated: ");
    fflush(stdin);
    scanf("%d", &n);
    // Create a new process
    pid_t pid = fork();
    // If the fork fails
    if(pid < 0) printf("Fork failed.\n");
    // Child process
    else if(pid == 0){
        printf("\nChild process.\n");
        printf("Even numbers: \n");
        // Loop through the indices in steps of 2 from 0
        for(int i = 0; i < n; i += 2)
            // Print the even numbers
            printf("%d\t", i);
        printf("\n");
    }
    // Parent process
    else {
        // Wait for the execution of the child
        wait(NULL);
        printf("\nParent process.\n");
        printf("Even numbers: \n");
        // Loop through the indices in steps of 2 from 1
        for(int i = 1; i < n; i += 2)
            // Print the odd numbers
            printf("%d\t", i);
        printf("\n");
    }
    exit(0);
}