#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int unnamed_pipe[2];

    if(pipe(unnamed_pipe) == -1) {
        printf("Error during creation unnamed pipe\n");
        exit(1);
    }

    pid_t proccess = fork();

    if(proccess == 0) {
        const char* msg = "Hi daddy Im your child!";

        if(write(unnamed_pipe[1], msg, strlen(msg) + 1) == -1) {
            printf("Error during writing message to pipe\n");
            exit(1);
        }

        close(unnamed_pipe[0]);
        close(unnamed_pipe[1]);
    }
    else {
        char msg[100]; 
        ssize_t bytes_read = read(unnamed_pipe[0], msg, sizeof(msg));

        if(bytes_read == -1) {
            printf("Error during reading message from pipe\n");
            exit(1);
        }

        strcat(msg, "Hi!");

        int outputfd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

        if(outputfd == -1) {
            printf("Error during creation a file for output\n");
            exit(1);
        }
        
        if(write(outputfd, msg, strlen(msg) + 1) == -1) {
            printf("Error during writing message in output\n");
            exit(1);
        }

        close(outputfd);

        close(unnamed_pipe[0]);
        close(unnamed_pipe[1]);
    }

    return 0;
}