// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Memoization cache
int cache[40];
// Function declaration
void* fib(void* params);

// Main function
int main(){
    int n;
    // Initialization the cache with -1
    memset(cache, -1, sizeof(cache));
    // Take the input from the user
    printf("Enter a number: ");
    scanf("%d", &n);
    // Call the fibonacci function
    fib(&n);
    // Printing the series
    for(int i = 0; i <= n; i++)
        printf("%d ", cache[i]);
    printf("\n");
}

// Fibonacci function
void* fib(void* params){
    // Storing the data from params to n 
    int* ptr = (int*) params;
    int n = *ptr;
    // If fib is not yet computed
    if (cache[n] == -1){
        // If the n(number) is less than 1 store that number itself in the cache
        if (n <= 1)
            cache[n] = n;
        // Else find the fib
        else{   
            pthread_t tid;
            // Storing the previous in x 
            int x = n - 1;
            // Create threads for each of the number
            pthread_create(&tid, NULL, fib, &x);
            // Joining those threads
            pthread_join(tid, NULL);
            // Again storing the previous value in x
            x = n - 2;
            // Calling the function recursively 
            fib(&x);
            cache[n] = cache[n - 1] + cache[n - 2];
        }
    }
}