#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

// Size of the contents that are copied 
#define BUFF_SIZE 1024

// Name of the file if the destination is a directory
char fileName[200];

void displayHelp();

// A function to revert the string
void reverse(char *x, int begin, int end){
    char c;
    // If the end is before begin, return null
    if (begin >= end)
        return;
    // Swap the characters
    c = *(x+begin);
    *(x+begin) = *(x+end);
    *(x+end) = c;
    // Recursive call
    reverse(x, ++begin, --end);
}

// A function to get the file name, if the destination is a directory
char* getFileName(char *path){
    // Last index of the path
    int pathLen = strlen(path) - 1, i = 0;
    // While the index is greater than -1
    while(pathLen >= 0){
        // If a / is encountered break
        if (path[pathLen] == '/')
            break;
        // Copy the filename part of the path
        fileName[i++] = path[pathLen--];
    }
    // Revert the filename
    reverse(fileName, 0, strlen(path) - 1);
    //return the filename
    return fileName;
}

// Main driver program with arguments
int main(int argc, char* argv[]){
	int src, dest, bytesRead;
	char *buff[BUFF_SIZE];

    int status;
    struct stat st_buf;

    if(strncmp(argv[1], "--help", 6) == 0){
        // Print the instructions on how to use the command
        displayHelp();
		exit(EXIT_SUCCESS);        
    }

    // If the length of the argument is not 3
	if(argc != 3){
        // Print the instructions on how to use the command
        printf("\033[1;31m");
        printf("Error: ");
        printf("\033[0;31m");
        printf("There must be one command, one source file and one destination file.\n");
        displayHelp();
		exit(EXIT_FAILURE);
	}

    // Open the source file with read only permissions
	src = open(argv[1],O_RDONLY);
 
    // If open is unsuccessful, exit with a failure
	if(src == -1){
		printf("\nError opening file %s \nError number: %d\n", argv[1], errno);
		exit(EXIT_FAILURE);	
	}

    // Get the status of the second file/directory
    status = stat(argv[2], &st_buf);

    // If the second argument is a directory
    if (S_ISDIR (st_buf.st_mode)) {
        // Concat the filename to the path
        strcat(argv[2], "/");
        strcat(argv[2], getFileName(argv[1]));
        // Create a file at the destination path
        FILE* fp = fopen(argv[2], "w");
        // Close the file
        fclose(fp);
    }

    // Open destination file with respective flags & modes
	// O_CREAT & O_TRUNC is to truncate existing file or create a new file
	// S_IXXXX are file permissions for the user,groups & others
    dest = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    //If open is unsuccessful, exit with a failure
    if(dest == -1)	{
		printf("\nError opening file %s \nError number: %d\n", argv[2], errno);
		exit(EXIT_FAILURE);
	}

    // While read is possible in src file
	while((bytesRead = read(src,buff,BUFF_SIZE)) > 0){
        // if the full string is not copied, exit with an error
		if(write(dest,buff,bytesRead) != bytesRead)
			printf("\nError in writing data to %s\n", argv[2]);
	}
	
    // If read in src file is possible
	if(bytesRead == -1)
		printf("\nError in reading data from %s\n", argv[1]);
	
    // If there is an error in closing src file
	if(close(src) == -1)
		printf("\nError in closing the source file\n");

    // If there is an error in closing dest file
	if(close(dest) == -1)
		printf("\nError in closing destination file\n");

    // Exit with success
	exit(EXIT_SUCCESS);
}

// A function to display help on usage of the command
void displayHelp(){
    printf("\033[1;36m");
    printf("\nUsage: ");
    printf("\033[0;36m");
    printf("./cpy source_file destination_file/destination_directory\n");
    printf("\033[0m");
    printf("\nIf you give a destination directory, the file name will also be copied.\n");
    printf("If you want a custom file name, give it yourself.\n");
    printf("\033[1;34m");
    printf("\nAvailable options: ");
    printf("\033[0;34m");
    printf("\n\n\t./cpy --help to display help and exit\n\n");
}