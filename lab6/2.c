// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

// Struct for the data
struct variables{
    int* a;
    int n;
};

// Function definitions
void* runner (void* args);
void bubbleSort(int* arr, int n, bool fun(const void*, const void*));
void print(int* arr, int n);
bool asc(const void* a, const void* b);
bool desc(const void* a, const void* b);
void swap(int* a, int* b);

/// Main driver function
int main(){
    struct variables data[2];
    // Scan the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &data[0].n);
    data[1].n = data[0].n;
    data[0].a = malloc(data[0].n * sizeof(int));
    data[1].a = malloc(data[1].n * sizeof(int));
    // Scan the numbers
    for (int i = 0; i < data[0].n; i++){
        printf("Enter the data at index %d: ", i + 1);
        scanf("%d", &data[0].a[i]);
        data[1].a[i] = data[0].a[i];
    }
    // Create a thread for the ascending sort
    pthread_t tid;
    pthread_create(&tid, NULL, runner, &data[0]);

    // Print the descending sort in the main thread
    printf("\nDescending sort: ");
    bubbleSort(data[1].a, data[1].n, desc);
    print(data[1].a, data[1].n);
    
    pthread_join(tid, NULL);
    return 0;
}

// Runner function for the pthresad
void* runner (void* args){
    struct variables* data = (struct variables *) args;
    printf("\nAscending sort: ");
    // Print the ascending sort
    bubbleSort(data->a, data->n, asc);
    print(data->a, data->n);
    // Exit the threads
    pthread_exit(0);
}

// A function for bubble sorting the array
void bubbleSort(int* arr, int n, bool fun(const void*, const void*)){
    // Loop through the array
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            // Call the function, if it returns true
            if (fun(&arr[j], &arr[j+1]))
                // Swap the numbers
                swap(&arr[j], &arr[j+1]);
}

// A function to print the array
void print(int* arr, int n){
    // Loop through the array
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// A function for ascending sort
bool asc(const void* a, const void* b){
    return *(int*)a > *(int*)b;
}

// A function for descending sort
bool desc(const void* a, const void* b){
    return *(int*)a < *(int*)b;
}

// A function to swap two variables
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}