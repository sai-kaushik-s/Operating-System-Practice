// Include the required libraries
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// Define the macros
#define ITERATIONS 10

// Global constants
sem_t mutex, writeblock;
int data = 0, rcount = 0;
int RWIdx[ITERATIONS];

// Function declarations
void *reader(void *params);
void *writer(void *params);

// Main driver function
int main(){
    pthread_t rtid[ITERATIONS], wtid[ITERATIONS];
    // Initialize the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);
    // Creates new threads
    for(int i = 0; i < ITERATIONS; i++){
        RWIdx[i] = i;
        pthread_create(&wtid[i], NULL, writer, (void *)&RWIdx[i]);
        pthread_create(&rtid[i], NULL, reader, (void *)&RWIdx[i]);
    }
    // Wait for termination of the threads
    for(int i = 0; i < ITERATIONS; i++){
        pthread_join(rtid[i], NULL);
        pthread_join(wtid[i], NULL);
    }
    // Destroy the semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeblock);
    return 0;
}

void *reader(void *params){
    int *f = params;
    // Lock the semaphore pointed to mutex 
    rcount = rcount + 1;
    // First reader
    if(rcount == 1)
        // Locks the semaphore pointed to writeblock
        sem_wait(&writeblock);
    // Unlock the semaphore pointed to mutex
    sem_post(&mutex);
    printf("Reader %d:\t%d\n", *f, data);
    // Locks the semaphore pointed to mutex 
    sem_wait(&mutex);
    rcount = rcount - 1;
    // Final reader
    if(rcount == 0)
        // Unlock the semaphore pointed to by writeblock
        sem_post(&writeblock);
    sleep(1);
    // Unlock the semaphore pointed to mutex
    sem_post(&mutex);
    pthread_exit(0);
}

void *writer(void *params){
    int *f = params;
    // Lock the semaphore pointed to writeblock
    sem_wait(&writeblock);
    // Update the data
    data++;
    printf("Writer %d:\t%d\n", *f, data);
    sleep(1);
    // Unlock the semaphore pointed to writeblock
    sem_post(&writeblock);
    pthread_exit(0);
}