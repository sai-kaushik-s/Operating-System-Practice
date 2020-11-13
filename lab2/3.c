#include<stdio.h>
#include<sys/types.h> 
#include<unistd.h>

int main(){
    int pid = fork();       //A
    if(pid < 0) fprintf(stderr, "Fork Failed");
    else if(pid == 0){
        fork();             //B
        printf("Child print\n");
    }
    else printf("Parent print\n");
    printf("Main print\n");
    return 0;
}