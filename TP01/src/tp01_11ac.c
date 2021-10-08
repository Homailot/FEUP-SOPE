#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define READ_BYTES 16

void end_func(void) {
    write(STDOUT_FILENO, "CLOSING...\n", 11);
}

int main(int argc, char * args[]) {
    atexit(end_func);
    if(argc < 2) {
        write(STDERR_FILENO, "INVALID ARGS SIZE\n", 18);
        exit(EXIT_FAILURE);
    }

    int in_file = open(args[1], O_RDONLY);

    if(in_file == -1) {
        write(STDERR_FILENO, "FAILED OPENING INPUT FILE: ", 27);
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    int out_file = STDOUT_FILENO;

    if(argc > 2) {
        // creat is open with O_CREAT | O_WRONLY | O_TRUNC

        out_file = creat(args[2], S_IRWXU | S_IRWXG | S_IRWXO);
    }

    if(out_file == -1) {
        write(STDERR_FILENO, "FAILED OPENING OUTPUT FILE: ", 28);
        perror(NULL);
        close(in_file);
        exit(EXIT_FAILURE);
    }

    char byte[READ_BYTES];
    int read_err;
    while((read_err = read(in_file, &byte, READ_BYTES)) != -1 && read_err != 0) {
        if(write(out_file, &byte, read_err) == -1) {
            write(STDERR_FILENO, "ERROR WHILE WRITING: ", 21);
            perror(NULL);
            close(in_file);
            close(out_file);
            exit(EXIT_FAILURE);
        }
    }
    if(read_err == -1) {
        write(STDERR_FILENO, "ERROR WHILE READING: ", 21);
        perror(NULL);
        close(in_file);
        close(out_file);
        exit(EXIT_FAILURE);
    }

    write(STDOUT_FILENO, "\nSUCCESS COPYING!\n", 18);
    close(in_file);
    close(out_file);
    exit(EXIT_SUCCESS);
}