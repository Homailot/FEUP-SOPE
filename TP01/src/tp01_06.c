#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char * args[]) {
    write(STDOUT_FILENO, "just a test\n", 12);
    fprintf(stdout, "just a test 2\n");

    if(argc != 2) {
        write(STDERR_FILENO, "INVALID ARG SIZE\n", 17);
        exit(EXIT_FAILURE);
    }

    int err = open(args[1], O_RDONLY);

    if(err == -1) {
        fprintf(stderr, "FAILED TO READ FILE\nRETURNED %d\nERROR NUMBER: %d\nERROR STRING: %s\nERROR STRING USING PERROR: ", err, errno, strerror(errno));
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    write(STDOUT_FILENO, "SUCCESS!\n", 9);
    exit(EXIT_SUCCESS);
}