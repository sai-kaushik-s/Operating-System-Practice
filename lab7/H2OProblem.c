// Include the required libraries
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Define the macros
#define HYDROGEN 10
#define OXYGEN 5

// Global constants
int oxygenNo = 0, hydrogenNo = 0, count = 0, flag = 0;
sem_t mutex, hydrogenSem, oxygenSem, barrier;

// Function declarations
void bond();
void *Hydrogen(void* params);
void *Oxygen(void* params);

// Main driver function
int main(){
    pthread_t htid[HYDROGEN], otid[OXYGEN];
    // Initialize the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&hydrogenSem, 0, 0);
    sem_init(&oxygenSem, 0, 0);
    sem_init(&barrier, 0, 3);
    int H[HYDROGEN], O[OXYGEN];
    // Creates new threads
    for (int i = 0; i < HYDROGEN; i++){
        H[i] = i;
        pthread_create(&htid[i], NULL, Hydrogen, (void *)&H[i]);
    }
    for (int i = 0; i < OXYGEN; i++){
        O[i] = i;
        pthread_create(&otid[i], NULL, Oxygen, (void *)&O[i]);
    }
    // Wait for termination of the threads
    for (int i = 0; i < HYDROGEN; i++)
        pthread_join(htid[i], NULL);
    for (int i = 0; i < OXYGEN; i++)
        pthread_join(otid[i], NULL);
    // Destroy the semaphores
    sem_destroy(&mutex);
    sem_destroy(&hydrogenSem);
    sem_destroy(&oxygenSem);
    sem_destroy(&barrier);
    return 0;
}

// A function to bond the atoms
void bond(){
    printf("H2O molecule bonded\n");
    count += 1;
    // If the molecule count is equal to oxygen count
    if (count == OXYGEN){
        // Exit the program
        printf("\nMaximum Generated Water Molecules: %d\n\n", count);
        exit(1);
    }
    sleep(1);
}

// A function to generate H atoms
void *Hydrogen(void* params){
    printf("H atom generated: %d\n", *((int *)params));
    while(1){
        // Lock the semaphore pointing at mutex
        sem_wait(&mutex);
        hydrogenNo += 1;
        // If there are more than 2 hydrogen and one oxygen
        if (hydrogenNo >= 2 && oxygenNo >= 1){
        // If there are more than 2 hydrogen and one oxygen
            sem_post(&hydrogenSem);
            // Decrement H atoms
            hydrogenNo -= 2;
            // Unlock the semaphore pointing at oxygenSem
            sem_post(&oxygenSem);
            // Decrement O atoms
            oxygenNo -= 1;
        }
        // Else
        else
            // Unlock the semaphore pointing at the mutex
            sem_post(&mutex);
        // Lock the semaphore pointing at the hydrogenSem
        sem_wait(&hydrogenSem);
        // Bond the atoms
        bond();
        // Lock the semaphore pointing at the barrier
        sem_wait(&barrier);
    }
    // Exit the thread
    pthread_exit(NULL);
}

// A function to generate O atoms
void *Oxygen(void* params){
    printf("Oxygen Molecule Generated: %d\n", *((int *)params));
    while (1){
        // Lock the semaphore pointing at mutex
        sem_wait(&mutex);
        oxygenNo += 1;
        // If there are more than 2 hydrogen and one oxygen
        if (hydrogenNo >= 2){
        // If there are more than 2 hydrogen and one oxygen
            sem_post(&hydrogenSem);
            // Decrement H atoms
            hydrogenNo -= 2;
            // Unlock the semaphore pointing at oxygenSem
            sem_post(&oxygenSem);
            // Decrement O atoms
            oxygenNo -= 1;
        }
        // Else
        else
            // Unlock the semaphore pointing at the mutex
            sem_post(&mutex);
        // Lock the semaphore pointing at the oxygenSem
        sem_wait(&oxygenSem);
        // Bond the atoms
        bond();
        // Lock the semaphore pointing at the barrier
        sem_wait(&barrier);
        // Unlock the semaphore pointing at the mutex
        sem_post(&mutex);
    }
    // Exit the thread
    pthread_exit(NULL);
}