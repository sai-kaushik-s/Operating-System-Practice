// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define MAX 1024

int low, high;
int sums[MAX];

// Function definitions
void* runner( void* params );

// Main driver function
int main(){
    // Scan the starting and ending point of the range
    printf("Enter the starting value: ");
    scanf("%d", &low);
    printf("Enter the ending value: ");
    scanf("%d", &high);

    // Create a thread
    for(int i = low; i <= high; i++){
        pthread_t tid;
        pthread_create(&tid, NULL, runner, &i);
        pthread_join(tid, NULL);
    }

    // Print the output
    printf("The set of armstrong numbers from %d to %d: {", low, high);
    for(int i = 0; i <= high - low; i++)
        // If the sum equals the number
        if(sums[i] == i + low)
            // Print the number
            printf("%d, ", i + 1);

    printf("\b\b}\n");
    return 0;
}

// Runner function for the pthread
void* runner(void* params){
    // Get the number
    int* val = (int*) params;
    int temp = *val;
    int i = 0;
    int sum = 0;

    // Count the number of digits in the digits
    while(temp){
        i++;
        temp = temp/10;
    }

    temp = *val;
    // Get the sum of the power of the digits
    while(temp){
        sum += pow( temp%10, i );
        temp = temp/10;
    }
    // Store it in the array
    sums[*val - low] = sum;
    // Exit the pthread
    pthread_exit(0);
}