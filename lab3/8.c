// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// Function declarations
int cache[100];
int fib(int n);

// Main driver function for the program
int main (){
    // Scan the number of elements to be generated
    int n;
    printf("Enter the number of terms to be generated: ");
    fflush(stdin);
    scanf("%d", &n);
    memset(cache, -1, 100);
    // Calculate fib of n
    fib(n);
    // Print the cache i.e. the fibonacci sequence
    printf("The set of first 'n' fibonacci series numbers are { ");
    for(int i = 0; i < n; i++)
        printf("%d, ", cache[i + 1]);
    printf("\b\b }\n");
    exit(0);
}

// A function to generate fibonacci of n
int fib(int n){
    int temp = 0;
    // If the fib of n is not yet computed
    if (cache[n] == -1){
        // Generate the initial numbers, i.e. 0 and 1
        if (n <= 1)
            cache[n] = n;
        else{
            // Create a new process
            pid_t pid = vfork();
            // If the fork fails
            if(pid < 0) printf("Fork failed.\n");
            // Child process
            else if(pid == 0){
                // Compute fib of n-1
                temp += fib(n - 1);
                exit(0);
            }
            // Parent process
            else {
                // Wait for the child to execute
                wait(NULL);
                // Compute fib of n-1
                temp += fib(n - 2);
            }
            // Update the cache
            cache[n] = temp;
        }
    }
    return cache[n];
}