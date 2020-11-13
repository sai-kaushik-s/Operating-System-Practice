#include<stdio.h>
#include<sys/types.h> 
#include<unistd.h>
#include<time.h>

int main(){
    int x = fork();         // Creates process 2
    if(x > 0){
        int y = fork();     // Creates process 3
        if(y > 0){
            int z = fork(); // Creates process 4
            if(z > 0)
                fork();     // Creates process 5
        }
        else if(y == 0){
            fork();         // Creates process 6
        }
    }
    else if(x == 0){
        fork();             // Creates process 7
    }
    printf("Hello\n");
}