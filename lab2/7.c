#include<stdio.h>
#include<sys/types.h> 
#include<unistd.h>
#include<time.h>

int main(){
    printf("This will be printed ?.\n", getpid());
    fork();
    printf("This will be printed ?.\n", getpid());
    fork();
    printf("This will be printed ? .\n", getpid());
    fork();
    printf("This will be printed ?\n", getpid());
    return 0;
}