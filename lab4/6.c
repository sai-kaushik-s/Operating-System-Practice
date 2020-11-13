//          __  __                               _             __          __
//         / /_/ /_  ___  ____ _____ _____ ___  (_)___  ____ _/ /_  ____  / /_
//        / __/ __ \/ _ \/ __ `/ __ `/ __ `__ \/ / __ \/ __ `/ __ \/ __ \/ __/
//       / /_/ / / /  __/ /_/ / /_/ / / / / / / / / / / /_/ / /_/ / /_/ / /_
//       \__/_/ /_/\___/\__, /\__,_/_/ /_/ /_/_/_/ /_/\__, /_.___/\____/\__/
//                     /____/                        /____/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
    int m1, n1, m2, n2;
    printf("Enter the number of rows of the first matrix: ");
    scanf("%d", &m1);
    printf("Enter the number of columns of the first matrix: ");
    scanf("%d", &n1);
    printf("Enter the number of rows of the second matrix: ");
    scanf("%d", &m2);
    printf("Enter the number of columes of the second matrix: ");
    scanf("%d", &n2);
    if (n1 != m2){
        printf("Matrix multiplication not possible.\n");
        exit(1);
    }
    int arr1[m1][n1], arr2[m2][n2], out[m1][n2];
    printf("The first matrix\n");
    for(int i = 0; i < m1; i++){
        for(int j = 0; j < n1; j++){
            printf("Enter the value at (%d, %d): ", i, j);
            scanf("%d", &arr1[i][j]);
        }
    }
    printf("The second matrix\n");
    for(int i = 0; i < m2; i++){
        for(int j = 0; j < n2; j++){
            printf("Enter the value at (%d, %d): ", i, j);
            scanf("%d", &arr2[i][j]);
        }
    }
    printf("The first matrix\n");
    for(int i = 0; i < m1; i++){
        for(int j = 0; j < n1; j++){
            printf("%d\t", arr1[i][j]);
        }
        printf("\n");
    }
    printf("The second matrix\n");
    for(int i = 0; i < m2; i++){
        for(int j = 0; j < n2; j++){
            printf("%d\t", arr2[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < m1; i++){
        for (int j = 0; j < n2; j++){
            out[i][j] = 0;
        }
    }
    for(int i = 0; i < m1; i++){
        for(int j = 0; j < n2; j++){
            pid_t pid = vfork();
            if(pid == 0){
                for(int k = 0; k < n1; k++)
                    out[i][j] += arr1[i][k] * arr2[k][j];
                exit(0);
            }
        }
    }
    printf("The output matrix\n");
    for(int i = 0; i < m1; i++){
        for(int j = 0; j < n2; j++){
            printf("%d\t", out[i][j]);
        }
        printf("\n");
    }
}