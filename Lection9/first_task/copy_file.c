#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void copyFile(const char* file_path, const char* copy_file_name) {
    struct stat stat_;
    int fromfd = open(file_path, O_RDONLY);
    
    if(fromfd < 0) {
        printf("Error during opening source file\n");
        exit(1);
    }

    fstat(fromfd, &stat_);

    int tofd = open(copy_file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    
    if(tofd < 0) {
        printf("Error during opening destination file\n");
        exit(1);
    }

    off_t offset = 0;
    int rv = sendfile(tofd, fromfd, &offset, stat_.st_size);

    if(rv < 0) {
        printf("Error during copying files\n");
        exit(1);
    }

    close(fromfd);
    close(tofd);
}