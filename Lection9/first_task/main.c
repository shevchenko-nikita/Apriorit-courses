#include <stdio.h>
#include <stdlib.h>

extern void copyFile(const char* file_path, const char* copy_file_name);

int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("Not enough arguments\n");
        exit(1);
    }

    const char* from = argv[1];
    const char* to = argv[2];

    copyFile(from, to);

    printf("Succsees\n");
}