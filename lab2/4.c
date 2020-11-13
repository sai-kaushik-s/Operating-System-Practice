#include<stdio.h>
#include<sys/types.h> 
#include<unistd.h>

int main(){
    int pid = fork();
    if(pid > 0){
        fork();
        printf("OS\n");
    }
    printf("Hello\n");
    return 0;
}