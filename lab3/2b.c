// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Main driver function for the program
int main(){
    // Scan the number of elements to be generated
    int n, x;
    printf("Enter the number of terms: ");
    fflush(stdin);
    scanf("%d", &n);
    int arr[n];
    // Scan for the elements from the user
    for(int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        fflush(stdin);
        scanf("%d", &arr[i]);
    }
    // Create a new process
    pid_t pid = vfork();
    // If the fork fails
    if(pid < 0) printf("Fork failed.\n");
    // Child process
    else if(pid == 0){
        x = 0;
        printf("\nChild process.\n");
        // Loop through the array in steps of 2 from 0
        for(int i = 0; i < n; i += 2)
            // Add the numbers
            x += arr[i];
        printf("Even indices sum: %d\n", x);
    }
    // Parent process
    else {
        // Wait for the execution of the child
        wait(NULL);
        x = 0;
        printf("\nParent process.\n");
        // Loop through the indices in steps of 2 from 1
        for(int i = 1; i < n; i += 2)
            // Add the numbers
            x += arr[i];
        printf("Odd indices sum: %d\n", x);
    }
    exit(0);
}