#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pp[2];
    char msg[1024];

    if (pipe(pp) == -1) {
        perror("pipe");
        exit(errno);
    }

    int id = fork();
    if (id == -1) {
        perror("fork");
        exit(errno);
    }

    switch (id) {
        case 0:
            close(pp[1]);
            if (read(pp[0], msg, 1024) < 0) {
                perror("read pipe");
                close(pp[0]);

                exit(errno);
            }
            close(pp[0]);

            strcat(msg, "Systems");
            printf("%s\n", msg);

            break;
        default:
            close(pp[0]);
            if (write(pp[1], "Operating ", 11) < 0) {
                perror("write pipe");
                close(pp[1]);

                exit(errno);
            }
            close(pp[1]);

            break;
    }

    return 0;
}