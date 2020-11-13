#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

void bubbleSortAsc(int* arr, int n);
void bubbleSortDesc(int* arr, int n);
void swap(int* a, int* b);
void print(int* arr, int n);
void displayHelp();

// Main driver program with arguments
int main(int argc, char* argv[]){
    // If the user ask for help on usage of the command
    if(strncmp(argv[1], "--help", 6) == 0 || argc < 4){
        // Print the instructions on how to use the command
        displayHelp();
		exit(EXIT_SUCCESS);
    }

    // Convert the size from string to int
    int size = atoi(argv[1]);
    char qw[] = ".";

    // If the size is negative or if there exists a floating point in the size
	if(size <= 0 || strstr(argv[1], qw)){
        // Print an error
        printf("\033[1;31m");
        printf("Error: ");
        printf("\033[0;31m");
        printf("The size of the array should be a positive non-zero integer.\n");
        // Print the instructions on how to use the command
        displayHelp();
        exit(EXIT_FAILURE);
    }

    // Convert the choice from string to int
    int choice = atoi(argv[2]);

    // If the choice is less than 1 or greater than two or if there exists a floating point in the choice
    if(choice < 1 || choice > 2 || strstr(argv[2], qw)){
        // Print an error
        printf("\033[1;31m");
        printf("Error: ");
        printf("\033[0;31m");
        printf("Choice should either be 1 for ascending sort or 2 for descending sort.\n");
        // Print the instructions on how to use the command
        displayHelp();
        exit(EXIT_FAILURE);
    }

    int arr[size];
    char a[MAX];

    // Loop through the test of the arguments
    for(int i = 3; i < argc; i++){
        // Convert the numbers from string to int
        arr[i - 3] = atoi(argv[i]);
        // Convert the numbers back to string from int
        sprintf(a, "%d", arr[i - 3]);
        // If the original arguments and converted arguments do not match
        if(strcmp(argv[i], a) != 0){
            printf("Enter only integers.\n");
            exit(EXIT_FAILURE);
        }
    }
    // If the choice is ascending
    if(choice == 1)
        bubbleSortAsc(arr, size);
    // If the choice is descending
    if(choice == 2)
        bubbleSortDesc(arr, size);
    // Print the sorted array
    print(arr, size);
    exit(EXIT_SUCCESS);
}

// A bubble sort function that sorts in ascending order
void bubbleSortAsc(int* arr, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

// A bubble sort function that sorts in descending order
void bubbleSortDesc(int* arr, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] < arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

// A function that prints the contents of an int array
void print(int* arr, int n){
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// A function that swaps two integers
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

// A function to display help on usage of the command
void displayHelp(){
    printf("\033[1;36m");
    printf("\nUsage: ");
    printf("\033[0;36m");
    printf("./sort0 array_length choice array_elements\n");
    printf("\033[0m");
    printf("\nArray length must be an integer and greater than 0.\n");
    printf("Choice: 1 for ascending sort and 2 for descending sort.\n");
    printf("Array elements must be separated by a space and must be integers.\n");
}