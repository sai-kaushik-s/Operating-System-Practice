#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int main() {
    int start, end, WCRP[2], WPRC[2];
    printf("Enter the beginning of the range: ");
    fflush(stdin);
    scanf("%d", &start);
    printf("Enter the ending of the range: ");
    fflush(stdin);
    scanf("%d", &end);

    int a[end - start + 1], z = 0;

    int n = end - start + 1, temp, count = 0, digit;
    int arr[n];
    for(int i = 0; i < n; i++)
        arr[i] = 0;
    
    if (pipe(WCRP) < 0) {
        perror("Could not pipe.\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(WPRC) < 0) {
        perror("Could not pipe.\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if(pid < 0) {
        perror("Could not fork.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        close(WCRP[0]);
        close(WPRC[1]);
        for(int i = start; i < end + 1; i++) {
            temp = i;
            while(temp != 0) {
                temp /= 10;
                count++;
            }
            temp = i;
            while(temp != 0) {
                digit = temp % 10;
                temp /= 10;
                arr[i - start] += pow(digit, count);
            }
            count = 0;
        }
        write(WCRP[1], &arr, sizeof(arr));
        read(WPRC[0], &z, sizeof(z));
        read(WPRC[0], &a, sizeof(a));
        printf("Set of Armstrong numbers between %d and %d are { ", start, end);
        for(int i = 0; i < z; i++)
            printf("%d, ", a[i]);
        printf("\b\b }\n");
    }
    else {
        close(WPRC[0]);
        close(WCRP[1]);
        read(WCRP[0], &arr, sizeof(arr));
        for(int i = start; i < end + 1; i++)
            if(arr[i - start] == i)
                a[z++] = i;
        write(WPRC[1], &z, sizeof(z));
        write(WPRC[1], &a, sizeof(a));
    }
    exit(0);
}