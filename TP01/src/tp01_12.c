#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* args[]) {
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    char command[120];

    snprintf(command, sizeof(command),
             "cd %s; ls -1 -s -S --block-size 1 | tail -n +2", args[1]);

    system(command);

    printf("for real now \n\n");

    DIR* directory = opendir(args[1]);

    if (directory == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent* directory_entry;

    chdir(args[1]);

    while ((directory_entry = readdir(directory)) != NULL)  {
        struct stat status;
        
        if(stat(directory_entry->d_name, &status)) {
            perror(NULL);
            continue;
        }

        printf("NAME= %s; SIZE= %ld\n", directory_entry->d_name, status.st_size);
    }

    closedir(directory);
}

// ./tp01_12 . | wc -l
// redirect output of this to tail and specify so that it outputs
// starting from line 2, ignoring the 'total size' first line.
// then redirect the output of tail to wc with the option -l to
// count the number of lines.