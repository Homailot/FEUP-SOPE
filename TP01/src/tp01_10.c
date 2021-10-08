#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
    const char* hello = "Hello world!\n";

    struct timespec tspec;
    clock_gettime(CLOCK_REALTIME, &tspec);

    for (int i = 0; i < 100000; i++) {
        write(STDOUT_FILENO, hello, 13);
    }

    struct timespec tspec2;
    clock_gettime(CLOCK_REALTIME, &tspec2);

    char output[1000];

    snprintf(output, sizeof(output), "%f\n",
             (double)((uint64_t)((tspec2.tv_sec - tspec.tv_sec) * 1e9) +
              (tspec2.tv_nsec - tspec.tv_nsec))/1e6);
    write(STDOUT_FILENO, output, strlen(output));

    exit(EXIT_SUCCESS);
}

// time ./tp01_10