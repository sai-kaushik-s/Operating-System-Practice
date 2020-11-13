// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

// Function declarations
void bubbleSort(int* arr, int n, bool fun(const void*, const void*));
void swap(int* a, int* b);
void print(int* arr, int n);
bool asc(const void* a, const void* b);
bool desc(const void* a, const void* b);

// Main driver function for the program
int main(){
    // Scan the number of elements
    int n;
    printf("Enter the number elements: ");
    fflush(stdin);
    scanf("%d", &n);
    int arr[n];
    // Scan the array elements
    for(int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        fflush(stdin);
        scanf("%d", &arr[i]);
    }
    // Create a new process
    pid_t pid = fork();
    // If the fork failed
    if(pid < 0) printf("Fork failed.\n");
    // Child process
    else if(pid == 0){
        printf("\nAscending sort.\n");
        // Create a new process
        pid_t child = vfork();
        // If the fork failed
        if(child < 0) printf("Fork failed.\n");
        // Child process
        else if(child == 0)
            // Bubble sort the array
            bubbleSort(arr, n, asc);
        // Parent process
        else{
            // Wait for the child process
            wait(NULL);
            // Print the sorted array
            print(arr, n);
        }
    }
    // Parent process
    else{
        // Wait for the child to complete
        wait(NULL);
        printf("\nDescending sort.\n");
        // Create a new process
        pid_t child = vfork();
        // If the fork failed
        if(child < 0) printf("Fork failed.\n");
        // Child process
        else if(child == 0)
            // Bubble sort the array
            bubbleSort(arr, n, desc);
        // Parent process
        else{
            // Wait for the child process
            wait(NULL);
            // Print the sorted array
            print(arr, n);
        }
    }
    exit(0);
}

// A function to bubble sort the array with a function pointer
void bubbleSort(int* arr, int n, bool fun(const void*, const void*)){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            // Check the output of the function pointer
            if (fun(&arr[j], &arr[j+1]))
                swap(&arr[j], &arr[j+1]);
}

// A function to print the array
void print(int* arr, int n){
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// A function that simulates the ascending sort condition
bool asc(const void* a, const void* b){
    return *(int*)a > *(int*)b;
}

// A function that simulates the descending sort condition
bool desc(const void* a, const void* b){
    return *(int*)a < *(int*)b;
}

// A function to swap two numbers
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}