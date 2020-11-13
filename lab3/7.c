// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

// Function declarations
int binarysearch(int *a, int n, int x);
void bubbleSort(int *arr, int n);
void swap(int *a, int *b);
void print(int *arr, int n);

// Main driver function for the program
int main(){
    // Scan the number of elements
    int n, mid, x, count = 0;
    printf("Enter the number elements: ");
    fflush(stdin);
    scanf("%d", &n);
    int arr[n];
    // Scan the array elements
    for (int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        fflush(stdin);
        scanf("%d", &arr[i]);
    }
    // Scan the search element
    printf("\nEnter the search key: ");
    fflush(stdin);
    scanf("%d", &x);
    // Sort the given array
    bubbleSort(arr, n);
    printf("\nThe sorted array\n");
    fflush(stdin);
    print(arr, n);
    // Create a new process
    pid_t pid = vfork();
    // If the fork fails
    if (pid < 0) printf("Fork failed.\n");
    // Child process
    else if (pid == 0){
        // If the search key is present in the array
        if ((mid = binarysearch(arr, n, x)) == -1){
            printf("%d is not found in the array\n", x);
            exit(1);
        }
        // Id the search key is absent in the array
        else
            printf("\n%d found at index %d\n", x, mid);
        exit(0);
    }
    // Parent process
    else{
        // Wait for the child process
        wait(NULL);
        int i = mid - 1;
        // Loop through the left of the search element to find the duplicates
        while (i > -1 && arr[i] == x){
            printf("%d found at index %d\n", x, i);
            i--;
        }
        i = mid + 1;
        // Loop through the right of the search element to find the duplicates
        while (i < n && arr[i] == x){
            printf("%d found at index %d\n", x, i);
            i++;
        }
    }
    exit(0);
}

// A function to implement binary search
int binarysearch(int *a, int n, int x){
    int l = 0, r = n - 1;
    // If there exists a number in the range
    while (l <= r){
        // Get the nid of the range
        int m = l + (r - l) / 2;
        // If the mid index is the key
        if (a[m] == x)
            return m;
        // If the array element is less than key
        else if (a[m] < x)
            // Update the lower range
            l = m + 1;
        // If the array element is greater than key
        else
            // Update the higher range
            r = m - 1;
    }
    return -1;
}

// A function to sort the array
void bubbleSort(int *arr, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

// A function to swap two numbers
void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

// A function to print the array
void print(int *arr, int n){
    for (int i = 0; i < n; i++)
        printf("Index %d: %d\n", i, arr[i]);
}
