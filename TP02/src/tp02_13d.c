#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_TRIES 100

int main() {
    int np;
    char msg[1024];
    u_int8_t tries = 0;

    if (mkfifo("/tmp/tp02_13d_pipe", 0777) < 0) {
        perror("fifo");
        return errno;
    }

    int id = fork();
    if (id == -1) {
        perror("fork");
        return errno;
    }

    switch (id) {
        case 0:
            while ((np = open("/tmp/tp02_13d_pipe", O_WRONLY)) < 0 &&
                   tries < MAX_TRIES)
                tries++;
            if (tries >= MAX_TRIES) {
                perror("open write pipe");
                return errno;
            }

            write(np, "Systems", 1 + strlen("Systems"));

            close(np);
            return 0;
            break;
        default:
            while ((np = open("/tmp/tp02_13d_pipe", O_RDONLY)) < 0 &&
                   tries < MAX_TRIES)
                tries++;
            if (tries >= MAX_TRIES) {
                perror("open read pipe");
                return errno;
            }

            read(np, msg, 1024);

            printf("Operating %s\n", msg);

            break;
    }

    close(np);

    if (waitpid(id, NULL, 0) == -1) {
        perror("wait");
        return errno;
    }

    errno = 0;
    if (unlink("/tmp/tp02_13d_pipe") == -1) {
        perror("unlink");
        return errno;
    }

    return 0;
}