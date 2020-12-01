// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Define the macros
#define BufferSize 5
#define Producer 0
#define Consumer 1

// Global constants
int in = 0, out = 0;
int buffer[BufferSize];
int flag[2] = {0, 0};
int turn = 0;

// Function declarations
void* producer(void *params);
void* consumer(void *params);
void printBuffer();

// Main driver function
int main(){
    srand(time(0));
    // Initialize the mutex and semaphores
    pthread_t ptid[BufferSize], ctid[BufferSize];
    // Create threads for producer and consumer
    for(int i = 0; i < BufferSize; i++)
        pthread_create(&ptid[i], NULL, (void *)producer, (void *)&i);
    for(int i = 0; i < BufferSize; i++)
        pthread_create(&ctid[i], NULL, (void *)consumer, (void *)&i);
    // Wait for the threads to complete
    for(int i = 0; i < BufferSize; i++)
        pthread_join(ptid[i], NULL);
    for(int i = 0; i < BufferSize; i++)
        pthread_join(ctid[i], NULL);
    return 0;
}

// A function for the producer
void* producer(void *params){
    // Entry Section
    flag[Producer] = 1;
    turn = Consumer;
    // Busy Wait
    while((flag[Consumer] ==1) && (turn==Consumer));
    // Critical Section
    // Get a random number in the range of 1 and 10
    int item = rand() % 10 + 1;
    // Add it to the buffer
    buffer[in] = item;
    printf("Producer: %d\tInserted Item: %d\tIndex: %d\n", *((int *)params), item, in);
    printBuffer();
    // Increment the buffer
    // Go around if pointer overflows
    in = (in + 1) % BufferSize;
    // Exit Section
    flag[Producer] = 0;
    sleep(2);
}

// A function for the consumer
void* consumer(void *params){
    // Entry Section
    flag[Consumer] = 1;
    turn = Producer;
    // Busy Wait
    while((flag[Producer]==1) && (turn==Producer));
    // Critical Section
    // Consume the buffer element
    int item = buffer[out];
    printf("Consumer: %d\tRemoved Item : %d\tIndex: %d\n", *((int *)params), item, out);
    printBuffer();
    // Increment the buffer
    // Go around if pointer overflows
    out = (out + 1) % BufferSize;
    // Exit Section
    flag[Consumer] = 0;
    sleep(2);
}

void printBuffer(){
    printf("Buffer array: ");
    for(int i = 0; i < BufferSize; i++)
        printf("%d ", buffer[i]);
    printf("\n\n");
}