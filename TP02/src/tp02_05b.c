#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


bool caught_sig = false;

void print_hello() {
    caught_sig = true;
}

int main() {
    // int pipefd[2];
    // char buf[100];
    // int readErr;

    // pipe(pipefd);
    // int id = fork();

    // if (id == -1) {
    //     perror(NULL);
    //     exit(EXIT_FAILURE);
    // }

    // switch (id) {
    //     case 0:
    //         close(pipefd[1]);
    //         while ((readErr = read(pipefd[0], &buf, 2)) > 0) printf("hey %d %s\n", readErr, buf)
    //             ;
    //         printf("err was %d\n", readErr);

    //         printf("Hello!\n");
    //         close(pipefd[0]);

    //         break;
    //     default:
    //         write(pipefd[1], "a", 2);

    //         printf("World: ");

    //         close(pipefd[0]);
    //         close(pipefd[1]);

    //         break;
    // }
    setbuf(stdout, NULL);

    struct sigaction act;
    struct sigaction oact;

    act.sa_handler = print_hello;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;

    sigaction(SIGUSR1, &act, &oact);

    int id = fork();

    switch (id) {
        case -1:
            exit(1);
            break;
        case 0:
            while(!caught_sig);
            printf("Hello!\n");
            break;
        default:
            printf("World: ");
            kill(id, SIGUSR1);
            break;
    }

    exit(0);
}