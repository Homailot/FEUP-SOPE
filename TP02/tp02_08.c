/*
*	Example of signals in action (with SIGACTION)
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void func(int signo) {
	printf("Hello!\n");
}

void func2(int signo) {
	printf("World: ");
}

int main() {
	struct sigaction new, old, new2;
	sigset_t smask;	// defines signals to block while func() is running

     // prepare struct sigaction
    if (sigemptyset(&smask)==-1)	// block no signal
        perror ("sigsetfunctions");

    new.sa_handler = func;
    new2.sa_handler = func2;
    new.sa_mask = smask;
    new2.sa_mask = smask;
    new.sa_flags = 0;	// usually works
    new2.sa_flags = 0;

    if(sigaction(SIGUSR1, &new, &old) == -1)
        perror ("sigaction");

    if(sigaction(SIGUSR2, &new2, &old) == -1)
        perror("sigaction");

    int id = fork();

    if(id == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    switch (id) {
        case 0:
            kill(getppid(), SIGUSR2);

            pause();	// wait
        default:
            pause();

            kill(id, SIGUSR1);
    }

	return 0;
}
