/*
 *	EXEC: 1st example of typical usage!
 *
 * Note:	execve is the syscal!
 *	execv, execvp, execvpe, execl, execlp, execle are library functions.
 *
 * Exercise:
 * 	change this code to show that USER was changed after the exec.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

// preparation for execve:
char* cmdline[] = {"sleep", "30", (void*)0};
char* newenviron[] = {"USER=Linus", NULL};

int main() {
    pid_t id;
    setbuf(stdout, NULL);  // to make sure printf() have no buffer so, nodelay!

    printf("\nParent: %d. USER=%s", getpid(), getenv("USER"));

    id = fork();
    switch (id) {
        case -1:
            perror("fork()");
            exit(1);
        case 0:  // child
            printf("\nChild: %d. USER=%s", getpid(), getenv("USER"));
            printf(
                "\nChild: check that following exec was succeful with: \"ps x "
                "| grep sleep\"\n");
            if (execle("/bin/sleep", "sleep", "30", NULL, newenviron) == -1)
                perror("execve");
            printf(
                "\nYou will not see this unless execve() fails! Know "
                "why?...\n");
            break;  // if execve fails...
        default:
            printf("\nParent still: %d. USER=%s", getpid(), getenv("USER"));
    }
    return 0;
}
