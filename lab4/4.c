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
#include <string.h>
#include <stdlib.h>

void history(char* cmd);

int main(){
    pid_t pid;
    char *command[2], *cmd = NULL, *line;
    size_t n, i;
    int status;
  
    while (1){
        char* cwd = getcwd(NULL, 0);
        printf("\033[1;34m\n%s", cwd);
        printf("\033[1;32m$ ");
        printf("\033[0m");
        getline(&cmd, &n, stdin);
        history(cmd);
        if (strncmp(cmd, "exit", 4) == 0)
            break;
        cmd = strtok(cmd, "\n");
        command[0] = strtok(cmd, " ");
        command[1] = strtok(NULL, " ");

        pid = fork();
        if (pid == 0){
            if (strncmp(command[0], "!", 1) == 0){
                command[0][0] = '0';
                int x = atoi(command[0]);
                FILE* fp = fopen(".history", "r");
                getline(&line, &i, fp);
                while(x){
                    getline(&line, &i, fp);
                    printf("%s", line);
                    x--;
                }
            }
            execlp(command[0], command[0], command[1], NULL);
        }
        if (pid > 0)
            wait(&status);
    } 
    free(cmd);
    exit(status);
}

void history(char* cmd){
    FILE* curr = fopen("1.txt", "w");

    fputs(cmd, curr);

    fclose(curr);

    system("cp .history 2.txt");
    system("cat 1.txt 2.txt > .history");
    system("rm 1.txt 2.txt");
}

void getHelp(){
    printf("Welcome to my shell!\n");
    printf("You can run all system executables.\n");
    printf("Supported functions are: ls, mkdir, gcc, g++...\n");
    printf("cd is not a system executable file. It is a shell bulletin.\n");
}