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

void histogram(char* filePath, char x);
void recursion(char* filePath, int i);

int main(){
    char filePath[100];
    printf("Enter the path of the file: ");
    scanf("%s", filePath);

    recursion(filePath, 0);
    return 0;
}

void histogram(char* filePath, char x){
    FILE* fp = fopen(filePath, "r");
    char c;
    int frequency = 0;
    do{
        c = fgetc(fp);
        if(feof(fp))
            break;
        if(c == x)
            frequency++;
    }
    while(1);
    printf("%c has a frequency of %d\n", x, frequency);
}

void recursion(char* filePath, int i){
    if(i < 95){
        pid_t pid = vfork();
        if(pid < 0){
            printf("Fork failed..\n");
            exit(1);
        }
        else if (pid == 0){
            char x = i + 32;
            histogram(filePath, x);
            exit(0);
        }
        else{
            wait(NULL);
            recursion(filePath, i + 1);
        }
    }
}