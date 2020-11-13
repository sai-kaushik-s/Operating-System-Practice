// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

// 2D pointer for the matrix
int** matrix;

bool isValid = true;

// Structure for the data
struct data{
    int row;
    int column;
};

// Function declarations
void* rowCheck(void* params);
void* columnCheck(void* params);
void* matrixCheck(void* params);

// Main driver function
int main(){
    // Initialize the array
    matrix = (int**)malloc(sizeof(int*)*9);
    for(int i = 0; i < 9; i++)
        matrix[i] = (int*)malloc(sizeof(int)*9);
    // Scan for the matrix
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            a:
            // If the input is greater than 9 or less than 1, take the input again
            printf("Enter the number [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
            if(matrix[i][j] < 1 || matrix[i][j] > 9){
                printf("The number should be in the range [1, 9].\n");
                goto a;
            }
        }
    }
    pthread_t tid[27];
    int x = 0;
    struct data params[27];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            // If the index mod 3 is 2, ie there are end index of a 3X3 matrix
            if (i % 3 == 2 && j % 3 == 2){
                params[x].column = j;
                params[x].row = i;
                // Check if the condition is satisfied
                pthread_create(&tid[x], NULL, matrixCheck, (void*)&params[x++]);
            }
            if(j == 0){
                params[x].column = j;
                params[x].row = i;
                // Check the column condition and row condition
                pthread_create(&tid[x], NULL, rowCheck, (void*)&params[x++]);
                params[x].column = j;
                params[x].row = i;
                pthread_create(&tid[x], NULL, columnCheck, (void*)&params[x++]);
            }
        }
    }
    // Wait for the threads to complete
    for(int i = 0; i < 27; i++)
        pthread_join(tid[i], NULL);
    // If the sudoku is not valid
    if(!isValid)
        printf("The given sudoku matrix is invalid.\n");
    // If the sudoku is valid
    else
        printf("The given sudoku matrix is valid.\n");
    exit(EXIT_SUCCESS);
}

// A function for row condition check
void* rowCheck(void* params){
    struct data* temp = (struct data* )params;
    int* sum = (int* )malloc(sizeof(int));
    // Initialize sum to 0
    *sum = 0;
    // Add the elements in the row
    for(int i = 0; i < 9; i++)
        *sum += matrix[temp->row][i];
    // If the sum is not 45, sudoku is invalid
    if (*sum != 45)
        isValid = false;
    // Exit the threads
    pthread_exit(NULL);
}

// A function for column condition check
void* columnCheck(void* params){
    struct data* temp = (struct data* )params;
    int* sum = (int* )malloc(sizeof(int));
    // Initialize sum to 0
    *sum = 0;
    // Add the elements in the column
    for(int i = 0; i < 9; i++)
        *sum += matrix[i][temp->column];
    // If the sum is not 45, sudoku is invalid
    if (*sum != 45)
        isValid = false;
    // Exit the threads
    pthread_exit(NULL);
}

// A function for 3X3 matrix condition check
void* matrixCheck(void* params){
    struct data* temp = (struct data* )params;
    int* sum = (int* )malloc(sizeof(int));
    // Initialize sum to 0
    *sum = 0;
    // Add the elements in the matrix
    for(int i = temp->row; i > temp->row - 3; i--)
        for(int j = temp->column; j > temp->column - 3; j--){
            *sum += matrix[i][j];
        }
    // If the sum is not 45, sudoku is invalid
    if (*sum != 45)
        isValid = false;
    // Exit the threads
    pthread_exit(NULL);
}