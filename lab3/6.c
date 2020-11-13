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
    int n, mid, x = 0;
    // Scan the number of elements
    printf("Enter the number elements: ");
    fflush(stdin);
    scanf("%d", &n);
    mid = n / 2;
    int arr1[mid], arr2[n - mid];
    // Scan the array elements
    for(int i = 0; i < mid; i++){
        printf("Enter number %d: ", ++x);
        fflush(stdin);
        scanf("%d", &arr1[i]);
    }
    for(int i = 0; i < n - mid; i++){
        printf("Enter number %d: ", ++x);
        fflush(stdin);
        scanf("%d", &arr2[i]);
    }
    // Create a new process
    pid_t pid = fork();
    // If the fork fails
    if(pid < 0) printf("Fork failed.\n");
    // Child process
    else if(pid == 0){
        printf("The ascending sort of the first half: ");
        // Create a new process
        pid_t child = vfork();
        // If the fork fails
        if(child < 0) printf("Fork failed.\n");
        // Child process
        else if(child == 0)
            // Bubble sort the first half of the array
            bubbleSort(arr1, mid, asc);
        // Parent process
        else{
            // Wait for the child to complete
            wait(NULL);
            // Print the array
            print(arr1, mid);
        }
    }
    // Parent process
    else{
        wait(NULL);
        printf("The descending sort of the second half: ");
        // Create a new process
        pid_t parent = vfork();
        // If the fork fails
        if(parent < 0) printf("Fork failed.\n");
        // Child process
        else if(parent == 0)
            // Bubble sort the second half of the array
            bubbleSort(arr2, n - mid, desc);
        // Parent process
        else{
            // Wait for the child to complete
            wait(NULL);
            // Print the array
            print(arr2, n - mid);
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