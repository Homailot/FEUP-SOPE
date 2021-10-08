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
        write(STDERR_FILENO, "INVALID ARGUMENT SIZE\n", 22);
        exit(1);
    }

    const char * first_file_name = args[1];

    int first_fileno = open(first_file_name, O_RDONLY);

    if(first_fileno < 0) {
        write(STDERR_FILENO, "FILE ERR\n", 10);
        exit(1);
    }

    int second_fileno = STDOUT_FILENO;

    if(argc > 2) {
        second_fileno = creat(args[2], S_IRWXG | S_IRWXO | S_IRWXU);
    }

    char read_chars[50];
    ssize_t read_bytes;
    while((read_bytes = read(first_fileno, read_chars, sizeof read_chars)) > 0) {
        write(second_fileno, read_chars, read_bytes);
    }

    close(first_fileno);
    close(second_fileno);
}