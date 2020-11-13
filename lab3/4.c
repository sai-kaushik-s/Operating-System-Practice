// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

// Function declarations
void primeNumberGenerator(int n);
int fib(int n);
void fibonacciSeriesGenerator(int n);

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
    // Child process: Generates the fibonacci series 
    else if(pid == 0) fibonacciSeriesGenerator(n);
    else {
        // Wait for the child to complete
        wait(NULL);
        // Generate prime numbers less than n
        primeNumberGenerator(n);
    }
    exit(0);
}

// A function to generate prime numbers
void primeNumberGenerator(int n){
    int flag;
    printf("The set of first 'n' prime numbers are { ");
    // Loop through 2 to n
    for (int i = 2; i <= n; i++){
        flag = 1;
        // Check if there are any factors from 2 to square root of i
        for (int j = 2; j <= sqrt(i); ++j){
            // If there is a factor
            if (i % j == 0){
                // Break the loop
                flag = 0;
                break;
            }
        }
        // If flag is 1 print the number
        if (flag == 1)
            printf("%d, ", i);
    }
    printf("\b\b }\n");
}

// A function that calculates fibonacci number recursively
int fib(int n){
    // Initial numbers are 0 and 1
    if (n <= 1)
        return n;
    // Return the sum of fibonacci of n-1 and n-2
    return fib(n-1) + fib(n-2);
}

// A function to generate fibonacci series
void fibonacciSeriesGenerator(int n){
    printf("The set of first 'n' fibonacci series numbers are { ");
    // Loop through the range
    for(int i = 0; i < n; i++)
        // Print the sequence
        printf("%d, ", fib(i + 1));
    printf("\b\b }\n");
}