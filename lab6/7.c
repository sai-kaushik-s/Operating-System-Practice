#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// Max number of threads
#define MAX_THREADS 4

// Function declaration
void* runner(void* params);
double randomGen();
// Declaring the count globally
long int count = 0;

// Main function
int main(){
    int n;
    // Take input from user for the number of points 
    printf("Enter number of points: ");
    scanf("%d", &n);

    pthread_t tid[MAX_THREADS];

    // Creating the thread (MAX_THREADS = 4) to generate n number of points 
    // Each thread will generate certain number of points based on the total count of threads (Here it is 4)
    for(int i = 0; i < MAX_THREADS; i++){
        int lr[] = {i * n / MAX_THREADS, (i + 1) * n / MAX_THREADS};
        pthread_create(&tid[i], NULL, runner, lr);
    }
    // Joining the threads
    for(int i = 0; i < MAX_THREADS; i++)
        pthread_join(tid[i], NULL);
    // Finding the value the pi
    double pi = 4 * (double)count / n;
    printf("The estimated value of pi: %f\n", pi);
}

// Runner function
void* runner(void* params){
    // Storing the data from params to temp
    int* temp = (int*)params;
    // Generating the random coordinates (random points)
    for(int i = temp[0]; i < temp[1]; i++){
        double x = randomGen();
        double y = randomGen();
        // If the generated coordinates satisfy the equation of the circle so it means the points life on or within the circle so increment the count
        double r = x * x + y * y;
        if (r <= 1)
            count++;
    }
}

double randomGen(){
    return ((double)rand() / (double)RAND_MAX);
}