#include <unistd.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    printf("%ld\n", sysconf(_SC_PAGESIZE));
}