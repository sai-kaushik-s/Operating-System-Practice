// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

// Main driver function for the program
int main(){
    int start, end;
    // Scan the start and end of the range
    printf("Enter the beginning of the range: ");
    fflush(stdin);
    scanf("%d", &start);
    printf("Enter the ending of the range: ");
    fflush(stdin);
    scanf("%d", &end);
    // Initialize the array to 0
    int n = end - start + 1, temp, count = 0, digit;
    int arr[n];
    for(int i = 0; i < n; i++)
        arr[i] = 0;
    // Create a new process
    pid_t pid = vfork();
    // If the fork fails
    if(pid < 0) printf("Fork failed.\n");
    // Child process
    else if(pid == 0){
        // Loop through the range
        for(int i = start; i < end + 1; i++){
            temp = i;
            // Get the count of digits
            while(temp != 0){
                temp /= 10;
                count++;
            }
            temp = i;
            // Loop through each digit
            while(temp != 0){
                digit = temp % 10;
                temp /= 10;
                // Compute the digit power count
                arr[i - start] += pow(digit, count);
            }
            count = 0;
        }
    }
    // Parent process
    else {
        // Wait for the child process to complete
        wait(NULL);
        printf("Set of Armstrong numbers between %d and %d are { ", start, end);
        // Loop through the range
        for(int i = start; i < end + 1; i++)
            // If the computer number is equal to the original number
            if(arr[i - start] == i)
                // It is an armstrong number
                printf("%d, ", i);
        printf("\b\b }\n");
    }
    exit(0);
}