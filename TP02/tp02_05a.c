#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>



int main() {
    int id = fork();

    if(id == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    switch (id) {
        case 0:
            printf("Hello ");
            break;
        default:
            // if(wait(NULL) == -1) {
            //     perror(NULL);
            //     exit(EXIT_FAILURE);
            // }
            if(waitpid(id, NULL, 0) == -1) {
                perror(NULL);
                exit(EXIT_FAILURE);
            }

            printf("World!\n");
            break;
    }
}