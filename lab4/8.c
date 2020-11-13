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

int** oddMagicSquare(int n) {
    if (n < 3 || n % 2 == 0)
        return NULL;

    int value = 0;
    int c = n / 2, r = 0;

    int** arr = (int**)malloc(n*sizeof(int*));

    for(int i = 0; i < n; i++)
        arr[i] = (int*)malloc(n*sizeof(int));

    while (++value <= n * n) {
        pid_t pid = vfork();
        if (pid == 0){
            arr[r][c] = value;
            if (r == 0) {
                if (c == n - 1) {
                    r++;
                }
                else {
                    r = n - 1;
                    c++;
                }
            }
            else if (c == n - 1) {
                r--;
                c = 0;
            }
            else if (arr[r - 1][c + 1] == 0) {
                r--;
                c++;
            }
            else {
                r++;
            }
            exit(0);
        }
    }
    return arr;
}

int** singlyEvenMagicSquare(int n) {
    if (n < 6 || n % 4 != 2)
        return NULL;

    int size = n * n;
    int half = n / 2;
    int subGridSize = size / 4, i;

    int** subGrid = oddMagicSquare(half);
    int gridFactors[] = {0, 2, 3, 1};
    int** arr = (int**)malloc(n*sizeof(int*));

    for(i=0;i<n;i++)
        arr[i] = (int*)malloc(n*sizeof(int));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            pid_t child = vfork();
            if(child == 0){
                int grid = (r / half) * 2 + (c / half);
                arr[r][c] = subGrid[r % half][c % half];
                arr[r][c] += gridFactors[grid] * subGridSize;
                exit(0);
            }
        }
    }

    int left = half / 2;
    int right = left - 1;

    for (int r = 0; r < half; r++)
        for (int c = 0; c < n; c++) {
            pid_t pid = vfork();
            if (pid == 0){
                if (c < left || c >= n - right || (c == left && r == left)) {
                    if (c == 0 && r == left)
                        exit(0);
                    int tmp = arr[r][c];
                    arr[r][c] = arr[r + half][c];
                    arr[r + half][c] = tmp;
                }
                exit(0);
            }
        }
    return arr;
}

int** doublyEvenMagicSquare(int n){
    if (n < 4 || n % 4 != 0)
        return NULL;

    int** arr = (int**)malloc(n*sizeof(int*));

    for(int i=0;i<n;i++)
        arr[i] = (int*)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            pid_t pid = vfork();
            if(pid == 0){
                arr[i][j] = (n*i) + j + 1;
                exit(0);
            }
        }

    for (int i = 0; i < n/4; i++)
        for (int j = 0; j < n/4; j++){
            pid_t pid = vfork();
            if(pid == 0){
                arr[i][j] = (n*n + 1) - arr[i][j];
                exit(0);
            }
        }

    for (int i = 0; i < n/4; i++)
        for (int j = 3 * (n/4); j < n; j++){
            pid_t pid = vfork();
            if(pid == 0){
                arr[i][j] = (n*n + 1) - arr[i][j];
                exit(0);
            }
        }

    for (int i = 3 * n/4; i < n; i++)
        for (int j = 0; j < n/4; j++){
            pid_t pid = vfork();
            if(pid == 0){
                arr[i][j] = (n*n+1) - arr[i][j];
                exit(0);
            }
        }

    for (int i = 3 * n/4; i < n; i++)
        for (int j = 3 * n/4; j < n; j++){
            pid_t pid = vfork();
            if(pid == 0){
                arr[i][j] = (n*n + 1) - arr[i][j];
                exit(0);
            }
        }

    for (int i = n/4; i < 3 * n/4; i++)
        for (int j = n/4; j < 3 * n/4; j++){
            pid_t pid = vfork();
            if(pid == 0){
                arr[i][j] = (n*n + 1) - arr[i][j];
                exit(0);
            }
        }

    return arr;
}

void printMagicSquare(int** square, int rows){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }
    printf("\nMagic constant: %d\n", (rows * rows + 1) * rows / 2);
}

int main(){
	int n;
	printf("Enter a number: ");
    scanf("%d", &n);
    if (n <= 2){
        printf("n should be greater than 2\n");
        exit(1);
    }
    if (n % 2 == 1)
        printMagicSquare(oddMagicSquare(n), n);
    else{
        if (n % 4 == 2)
            printMagicSquare(singlyEvenMagicSquare(n), n);
        else if(n % 4 == 0)
            printMagicSquare(doublyEvenMagicSquare(n), n);
    }
    exit(0);
}