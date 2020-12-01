// Include the required libraries
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

// Define the macros
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (PhilNo + 4) % N
#define RIGHT (PhilNo + 1) % N
#define ITERATIONS 3

// Global constants
sem_t mutex;
sem_t S[N];
int state[N];
int PhilNoArr[N] = {0, 1, 2, 3, 4};

// Function declarations
void *philosopher(void *params);
void takeFork(int);
void putFork(int);
void test(int);

// Main driver function
int main(){
    pthread_t tid[N];
    // Initialize the semaphores
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);
    // Create new threads
    for(int i = 0; i < N; i++){
        pthread_create(&tid[i], NULL, philosopher, &PhilNoArr[i]);
        printf("Philosopher %d\tThinking\n", i+1);
    }
    // Wait for termination of the threads
    for(int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);
    // Destroy the semaphores
    sem_destroy(&mutex);
    for(int i = 0; i < N; i++)
        sem_destroy(&S[i]);
    return 0;
}

// A function to run the actions of a philosopher
void *philosopher(void *params){
    for(int j = 0; j < ITERATIONS; j++){
        int *i = params;
        sleep(1);
        // Use the fork
        takeFork(*i);
        printf("Philosopher %d\tFinished eating\n", *i+1);
        // Put the fork back on the table
        putFork(*i);
    }
    pthread_exit(0);
}

// A function to take forks from the table
void takeFork(int PhilNo){
    // Lock the semaphore pointed to mutex to keep the update in the critical section
    sem_wait(&mutex);
    state[PhilNo] = HUNGRY;
    printf("Philosopher %d\tHungry\n", PhilNo + 1);
    // Test the philosopher
    test(PhilNo);
    // Unlocks the semaphore pointed to mutex
    sem_post(&mutex);
    // Lock the semaphore pointed to S[PhilNo]
    sem_wait(&S[PhilNo]); 
    sleep(1);
}

// A function to put the fork back on the table
void putFork(int PhilNo){
    // Lock the semaphore pointed to mutex to keep the update in the critical section
    sem_wait(&mutex);
    // Change state to thinking
    state[PhilNo] = THINKING;
    printf("Philosopher %d\tPuts fork %d and %d down\n", PhilNo + 1, LEFT + 1, PhilNo + 1);
    printf("Philosopher %d\tThinking\n", PhilNo + 1);
    // Test his neighbors
    test(LEFT);
    test(RIGHT);
    // Unlocks the semaphore pointed to mutex
    sem_post(&mutex);
}

// A function to test the state of a given philosopher
void test(int PhilNo){
    // If the current philosopher is hungry and there are forks unused
    if(state[PhilNo] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        // Change the state of PhilNo
        state[PhilNo] = EATING;
        sleep(2);
        printf("Philosopher %d\tUses fork %d and %d\n", PhilNo + 1, LEFT + 1, PhilNo + 1);
        printf("Philosopher %d\tEating\n", PhilNo + 1);
        // Unlocks the semaphore pointed to S[PhilNo]
        sem_post(&S[PhilNo]);
    }
}