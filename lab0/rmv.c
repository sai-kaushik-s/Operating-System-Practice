#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 1024

void displayHelp();

// A function to recursively remove directories
int removeDir(char* path){
    struct dirent *de;
    char fname[300];
    // Open the directory
    DIR *dr = opendir(path);
    // If the directory does not exist
    if(dr == NULL){
        printf("No file or directory found\n");
        exit(EXIT_FAILURE);
    }
    // Read the directory and loop through it
    while((de = readdir(dr)) != NULL){
        int ret = -1;
        struct stat statbuf;
        // Concat the path to the file name
        sprintf(fname,"%s/%s",path,de->d_name);
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;
        // If the directory or file exists
        if(!stat(fname, &statbuf)){
            // If the content is a directory
            if(S_ISDIR(statbuf.st_mode)){
                // Unlink the directory
                ret = unlinkat(dirfd(dr),fname,AT_REMOVEDIR);
                // Recursively call the removeDir function
                if(ret != 0){
                    removeDir(fname);
                    ret = unlinkat(dirfd(dr),fname,AT_REMOVEDIR);
                }
            }
            // If the content is a file
            else
                // Unlink the file
                unlink(fname);
        }
    }
    // Close the directory
    closedir(dr);
    // Remove the directory
    rmdir(path);
}

// Main driver program with arguments
int main(int argc, char* argv[]){
    int status;
    struct stat st_buf;

    // If the user asks for help
    if(strncmp(argv[1], "--help", 6) == 0){
        // Print the instructions on how to use the command
        displayHelp();
		exit(EXIT_SUCCESS);        
    }

    // If there are less arguments than required
	if(argc < 2){
        // Print the error and usage
        printf("\033[1;31m");
        printf("Error: ");
        printf("\033[0;31m");
        printf("There must be one command, and at least one file/directory to be removed.\n");
        printf("\033[1;36m");
		displayHelp();
		exit(EXIT_FAILURE);
	}

    // Option -r recursive
    if(strncmp(argv[1], "-r", 2) == 0){
        // Loop through all the argv
        for(int i = 2; i < argc; i++){
            // Get the status of the content
            status = stat (argv[i], &st_buf);
            // If the content is a directory
            if (S_ISDIR (st_buf.st_mode)){
                // Call the removeDir function
                char path[MAX];
                getcwd(path, MAX);
                char* x = strcat(path, "/");
                x = strcat(x, argv[i]);
                removeDir(x);
            }
            // If the content is a file
            else
                // Remove the file
                remove(argv[i]);
        }
        exit(EXIT_SUCCESS);
    }
    // For normal rmv, loop through argv
    for (int i = 1; i < argc; i++){
        // remove the file
        remove(argv[i]);
    }
	exit(EXIT_SUCCESS);
}

// A function to display help on usage of the command
void displayHelp(){
    printf("\033[1;36m");
    printf("\nUsage: ");
    printf("\033[0;36m");
    printf("./rmv source_files\n");
    printf("\033[1;34m");
    printf("\nAvailable options: ");
    printf("\033[0;34m");
    printf("\n\n\t./rmv --help to display help and exit\n");
    printf("\t./rmv --r directory_paths to recursively remove the directories.\n\n");
}