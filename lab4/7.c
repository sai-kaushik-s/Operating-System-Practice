//          __  __                               _             __          __
//         / /_/ /_  ___  ____ _____ _____ ___  (_)___  ____ _/ /_  ____  / /_
//        / __/ __ \/ _ \/ __ `/ __ `/ __ `__ \/ / __ \/ __ `/ __ \/ __ \/ __/
//       / /_/ / / /  __/ /_/ / /_/ / / / / / / / / / / /_/ / /_/ / /_/ / /_
//       \__/_/ /_/\___/\__, /\__,_/_/ /_/ /_/_/_/ /_/\__, /_.___/\____/\__/
//                     /____/                        /____/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int MagicSquareCheck(int** arr, int size);
void printMagicSquare(int** square, int rows);
int isMagicSquare = 1;

int main(){
    int n;
    printf("Enter the number of rows/columns in the square: ");
    scanf("%d", &n);
    int** arr = (int**) malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
        arr[i] = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("Enter the element arr[%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
    printf("\nThe magic square is: \n\t");
    printMagicSquare(arr, n);
    MagicSquareCheck(arr, n);
    if(isMagicSquare == 1)
        printf("\nThe entered square is a magic square.\n");
    else
        printf("\nThe entered square is not a magic square.\n");
    return 0;
}

int MagicSquareCheck(int** arr, int size){
    int sum1 = 0, sum2 = 0;

    for(int i = 0; i < size; i++)
        sum1 = sum1 + arr[i][i];

    for(int i = 0; i < size; i++)
        sum2 = sum2 + arr[i][size-1-i];
    if(sum1 != sum2){
        isMagicSquare = 0;
        exit(1);
    }

    for(int i = 0; i < size; i++){
        int rowSum = 0;
        pid_t pid = vfork();
        if(pid == 0){
            for(int j = 0; j < size; j++)
                rowSum += arr[i][j];
            if(rowSum != sum1){
                isMagicSquare = 0;
                exit(1);
            }
            exit(0);
        }
    }

    for(int i = 0; i < size; i++){
        int colSum = 0;
        pid_t pid = vfork();
        if(pid == 0){
            for(int j = 0; j < size; j++)
                colSum += arr[j][i];
            if(sum1 != colSum){
                isMagicSquare = 0;
                exit(1);
            }
            exit(0);
        }
    }
    return 1;
}

void printMagicSquare(int** square, int rows){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            printf("%4d ", square[i][j]);
        }
        printf("\n\t");
    }
}