#include<stdio.h>
#include<sys/types.h> 
#include<unistd.h>

int main(){
    pid_t pid = fork();
    if(pid != 0) fork();
    fork();
    printf("Count\n");
    return 0;
}