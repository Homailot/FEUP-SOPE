#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * args[]) {
    if(argc < 2) {
        exit(EXIT_FAILURE);
    }

    char command[120];
    
    sprintf(command, "cd %s; ls -1 -s -S --block-size 1 | tail -n +2", args[1]);

    system(command);
}

// ./tp01_12 . | wc -l
// redirect output of this to tail and specify so that it outputs
// starting from line 2, ignoring the 'total size' first line.
// then redirect the output of tail to wc with the option -l to 
// count the number of lines.