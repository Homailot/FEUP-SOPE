#include <stdio.h>
#include <stdlib.h>

#define READ_BYTES 16

void end_func(void) {
    printf("CLOSING...\n");
}

int main(int argc, char * args[]) {
    atexit(end_func);
    if(argc < 2) {
        fprintf(stderr, "INVALID ARGS SIZE %d\n", argc);
        exit(EXIT_FAILURE);
    }

    FILE * in_file = fopen(args[1], "r");

    if(in_file == NULL) {
        perror("FAILED OPENING INPUT FILE");
        exit(EXIT_FAILURE);
    }

    FILE * out_file = stdout;

    if(argc > 2) {
        // w mode is the same as creat.

        out_file = fopen(args[2], "w");
    }

    if(out_file == NULL) {
        perror("FAILED OPENING OUTPUT FILE");
        fclose(in_file);
        exit(EXIT_FAILURE);
    }

    char byte[READ_BYTES];
    int read_err;
    while((read_err = fread(byte, 1, READ_BYTES, in_file)) != 0) {
        if(fwrite(byte, 1, read_err, out_file) == 0 && ferror(out_file)) {
            perror("ERROR WHILE WRITING");
            fclose(in_file);
            fclose(out_file);
            exit(EXIT_FAILURE);
        }
    }
    if(read_err == 0 && ferror(in_file)) {
        perror("ERROR WHILE READING");
        fclose(in_file);
        fclose(out_file);
        exit(EXIT_FAILURE);
    }

    printf("\nSUCCESS COPYING!\n");
    fclose(in_file);
    fclose(out_file);
    exit(EXIT_SUCCESS);
}