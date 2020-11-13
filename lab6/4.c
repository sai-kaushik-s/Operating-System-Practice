// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define MAX_THREADS 5

// Struct for the data
struct range
{
    int low;
    int high;
};

// Function definitions
void* prime(void* params);

// Main driver function
int main(int argc , char *argv[])
{
    // Usage: ./<outout_binary> <a_number>
    if(argc != 2){
        printf("Usage %s [number] \n", argv[0]);
        exit(0);
    }
    // Convert the string to int
    int n = atoi(argv[1]);
    struct range lh[MAX_THREADS];
    // Split the given int into MAX_THREADS pieces
    for (int i = 0; i < MAX_THREADS; i++){
        lh[i].low = i*(n/MAX_THREADS);
        lh[i].high = (i+1)*(n/MAX_THREADS);
    }
    printf("The set of %d prime numbers are { ", n);
    pthread_t tid[MAX_THREADS];
    // Create MAX_THREADS number of threads
    for(int i = 0; i < MAX_THREADS; i++)
        pthread_create(&tid[i], NULL, prime, &lh[i]);
    // Wait until all the threads exit
    for(int i = 0; i < MAX_THREADS; i++)
        pthread_join(tid[i], NULL);
    printf("\b\b }\n");
}

// A function to generate the prime numbers
void* prime(void* params){
    int flag;
    struct range* lh = (struct range*) params;
    // Loop from the start to end
    for (int i = lh->low; i <= lh->high; i++){
        // 1 and 0 are not primes
        if (i == 1 || i == 0)
            continue;
        flag = 1;
        // Loop till square root of the number
        for (int j = 2; j <= sqrt(i); ++j){
            // If there exits a perfect divisor
            if (i % j == 0){
                flag = 0;
                // Break the loop
                break;
            }
        }
        // If the number is a prime
        if (flag == 1)
            printf("%d, ", i);
    }
    // Exit the thread
    pthread_exit(0);
}
