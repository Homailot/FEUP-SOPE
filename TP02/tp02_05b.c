#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>



int main() {
    int pipefd[2];
    char buf;
    int readErr;

    pipe(pipefd);
    int id = fork();

    if(id == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }


    switch (id) {
        case 0:
            close(pipefd[1]);
            while((readErr = read(pipefd[0], &buf, 1)) > 0);

            printf("Hello!\n");
            close(pipefd[0]);

            break;
        default:
            printf("World: ");
            
            close(pipefd[0]);
            close(pipefd[1]);
            
            break;
    }
}