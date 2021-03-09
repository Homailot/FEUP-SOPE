/*
 *	EXEC: 1st example of typical usage!
 *
 * Note:	execve is the syscal!
 *	execv, execvp, execvpe, execl, execlp, execle are library functions.
 *
 * Exercise:
 * 	change this code to show that USER was changed after the exec.
 */
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

// preparation for execve:
char* cmdline[] = {"tp03_02c", "q", (void*)0};
char* newenviron[] = {"USER=Linus", NULL};

int main(int argc, char * args[], char* envp[]) {
    pid_t id;
    int status;
    setbuf(stdout, NULL);  // to make sure printf() have no buffer so, nodelay!

    printf("\nParent: %d. USER=%s\n", getpid(), getenv("USER"));
    if(argc > 1 && args[1][0] == 'q') return 1; 

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
            if (execve("./tp03_02c", cmdline, newenviron) == -1)
                perror("execve");
            printf(
                "\nYou will not see this unless execve() fails! Know "
                "why?...\n");
            break;  // if execve fails...
        default:
            printf("\nParent still: %d. USER=%s", getpid(), getenv("USER"));

            if (waitpid(id, &status, 0) == -1) {
                perror("wait");
                return 1;
            }
            printf("status of process: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
