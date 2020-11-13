// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struct for the data
struct data{
    int* a;
    int n;
    int idx;
    int x;
};

// Function definitions
void* runner(void* params);
int binarysearch(int *a, int n, int x);
void bubbleSort(int *arr, int n);
void swap(int *a, int *b);
void print(int *arr, int n);

/// Main driver function
int main(){
    struct data argv;
    // Get the number of elements
    printf("Enter the number elements: ");
    fflush(stdin);
    scanf("%d", &argv.n);
    argv.a = (int *) malloc(sizeof(int) * argv.n);
    // Get the elements of the array
    for (int i = 0; i < argv.n; i++){
        printf("Enter number %d: ", i + 1);
        fflush(stdin);
        scanf("%d", &argv.a[i]);
    }
    // Get the search element
    printf("\nEnter the search key: ");
    fflush(stdin);
    scanf("%d", &argv.x);
    // Sort the array
    bubbleSort(argv.a, argv.n);
    printf("\nThe sorted array\n");
    fflush(stdin);
    print(argv.a, argv.n);
    // Binary search the array for the search element
    argv.idx = binarysearch(argv.a, argv.n, argv.x);
    // If the return value is -1
    if(argv.idx == -1){
        // Exit the program
        printf("\n%d not found in the array.\n", argv.x);
        exit(0);
    }
    printf("\n%d found at index %d.\n", argv.x, argv.idx);
    // Create a new thread to search the left part
    pthread_t tid;
    pthread_create(&tid, NULL, runner, &argv);
    pthread_join(tid, NULL);
    // Search the right part in the main thread
    int i = argv.idx + 1;
    while (argv.a[i] == argv.x && i < argv.n){
        printf("%d found at index %d.\n", argv.x, i);
        i++;
    }
}

// Runner function for the thread
void* runner(void* params){
    // Search the left part of the array
    struct data* argv = (struct data *) params;
    int i = argv->idx - 1;
    while (argv->a[i] == argv->x && i > -1){
        printf("%d found at index %d.\n", argv->x, i);
        i--;
    }
    // Exit the thread
    pthread_exit(NULL);
}

// A function to implement binary search
int binarysearch(int *a, int n, int x){
    int l = 0, r = n - 1;
    while (l <= r){
        // Check the mid of the range
        int m = l + (r - l) / 2;
        if (a[m] == x)
            return m;
        // If the mid is less than search element 
        else if (a[m] < x)
            // Update the start of the range
            l = m + 1;
        // If the mig is greater than search element
        else
            //Update the end of the range
            r = m - 1;
    }
    // If element not found
    return -1;
}

// A function to implement bubble sort
void bubbleSort(int *arr, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

// A function to swap the elements
void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

// Print the array
void print(int *arr, int n){
    for (int i = 0; i < n; i++)
        printf("Index %d: %d\n", i, arr[i]);
}