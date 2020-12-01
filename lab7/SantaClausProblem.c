// Include the required libraries
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>

// Define the macros
#define ELVES 10
#define REINDEER 9
#define ITERATIONS 3

// Global constants
int elves = 0, reindeer = 0;
sem_t santaSem, reindeerSem, elfSem, mutex;

// Function declarations
void *SantaClaus(void *params);
void *Reindeer(void *params);
void *Elf(void *params);

// Main driver function
int main(){
    // Initialize the semaphores
	sem_init(&santaSem, 0, 0);
	sem_init(&reindeerSem, 0, 0);
	sem_init(&elfSem, 0, 1);
	sem_init(&mutex, 0, 1);
    int reindeerArr[REINDEER], elfArr[ELVES];
	pthread_t santa_claus, reindeers[REINDEER], elves[ELVES];
    // Creates a new thread for Santa, Reindeers and Elves
    pthread_create(&santa_claus, NULL, SantaClaus, (void *)0);
	for (int i = 0; i < REINDEER; i++){
        reindeerArr[i] = i;
        pthread_create(&reindeers[i], NULL, Reindeer, (void *)&reindeerArr[i]);
    }
	for (int i = 0; i < ELVES; i++){
        elfArr[i] = i;
        pthread_create(&elves[i], NULL, Elf, (void *)&elfArr[i]);
    }
    // Wait for termination of the threads
	pthread_join(santa_claus, NULL);
    for (int i = 0; i < REINDEER; i++)
        pthread_join(reindeers[i], NULL);
	for (int i = 0; i < ELVES; i++)
        pthread_join(elves[i], NULL);
    // Destroy the semaphores
    sem_destroy(&santaSem);
    sem_destroy(&reindeerSem);
    sem_destroy(&elfSem);
    sem_destroy(&mutex);
}

// A function to manage tasks of Santa Claus
void *SantaClaus(void *params){
	printf("Santa Claus reporting to duty\n");
    // Loop the tasks
	for(int i = 0; i < ITERATIONS; i++){
        // Lock the semaphore pointing at santaSem and mutex
		sem_wait(&santaSem);
		sem_wait(&mutex);
        // Final reindeer
		if (reindeer == REINDEER){
			printf("Santa Claus: Prepping the sleigh\n");
            // Unlock all reindeerSem
			for (int j = 0; j < REINDEER; j++)
				sem_post(&reindeerSem);
			printf("Santa Claus: Make all kids happy\n");
            // Reset reindeer flag
			reindeer = 0;
		}
        // Help every third elf
		else if (elves == 3)
			printf("Santa Claus: Helping elves\n");
        // Unlock the semaphore pointing at mutex
		sem_post(&mutex);
	}
    // Unlock the semaphore pointing at santaSem
    sem_post(&santaSem);
}

// A function to manage tasks of Reindeer
void *Reindeer(void *params){
	int id = *((int *)params);
	printf("Reindeer %d reporting to duty\n", id);
    // Loop the tasks
	for(int i = 0; i < ITERATIONS; i++){
        // Lock the semaphore pointing at mutex
		sem_wait(&mutex);
		reindeer++;
        // Final reindeer
		if (reindeer == REINDEER)
            // Unlock the semaphore pointing at santaSem
			sem_post(&santaSem);
        // Unlock the semaphore pointing at mutex
		sem_post(&mutex);
        // Unlock the semaphore pointing at reindeerSem
		sem_wait(&reindeerSem);
		printf("Reindeer %d getting hitched\n", id);
		sleep(20);
	}
}

// A function to manage tasks of Elf
void *Elf(void *params){
	int id = *((int *)params);
	printf("Elf %d reporting to duty\n", id);
    // Loop the tasks
	for(int i = 0; i < ITERATIONS; i++){
		bool need_help = random() % 100 < 10;
        // If help needed
		if (need_help){
            // Lock the semaphore pointing at elfSem and mutex
			sem_wait(&elfSem);
			sem_wait(&mutex);
			elves++;
            // Every third elf
			if (elves == 3)
                // Unlock the semaphore pointing at santaSem
				sem_post(&santaSem);
            // Else
			else
                // Unlock the semaphore pointing at elfSem
				sem_post(&elfSem);
            // Unlock the semaphore pointing at mutex
			sem_post(&mutex);
			printf("Elf %d will get help from Santa Claus\n", id);
			sleep(10);
            // Lock the semaphore pointing at mutex
			sem_wait(&mutex);
			elves--;
            // If all work is done
			if (elves == 0)
                // Unlock the semaphore pointing at elfSem
				sem_post(&elfSem);
            // Unlock the semaphore pointing at mutex
			sem_post(&mutex);
		}
		printf("Elf %d at work\n", id);
		sleep(2 + random() % 5);
	}
}