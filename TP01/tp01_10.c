#include <unistd.h>
#include <stdlib.h>

int main() {
    const char * hello = "Hello world!\n";

    for(int i = 0; i < 100000; i++) {
        write(STDOUT_FILENO, hello, 13);
    }
    
    exit(EXIT_SUCCESS);
}

// time ./tp01_10