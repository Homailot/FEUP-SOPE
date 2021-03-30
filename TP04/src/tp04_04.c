#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1000000

int main(int argc, char* args[]) {
    int * mem[SIZE];
    int i = 0;

    while((mem[i] = malloc(500*(2^100))) != NULL) {
        printf("hello %d\n", i);
        mem[i] = memset(mem[i], 'A', 500*(2^100) - 1);

        i++;
        if(i >= SIZE) break;
    }

    perror("malloc");
    return errno;
}
