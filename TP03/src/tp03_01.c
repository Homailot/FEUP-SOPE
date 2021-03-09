#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int recursive_inner(const char* pathname, int depth) {
    DIR* cur_dir = opendir(pathname);

    if (cur_dir == NULL) {
        perror("opendir");
        return errno;
    }

    struct dirent* directory_entry;
    struct stat status;
    char new_path[(depth + 2) * MAXNAMLEN + 2];

    errno = 0;
    while ((directory_entry = readdir(cur_dir)) != NULL) {
        if (strcmp(directory_entry->d_name, "..") == 0 ||
            strcmp(directory_entry->d_name, ".") == 0)
            continue;

        sprintf(new_path, "%s/%s", pathname, directory_entry->d_name);

        if (stat(new_path, &status)) {
            perror("stat error");
            return errno;
        }

        printf("%s, with size %ld\n", new_path, status.st_size);

        if (S_ISDIR(status.st_mode)) {
            fflush(NULL);
            int id = fork();
            if (id == -1) {
                perror("fork");
                return errno;
            }

            if (id == 0) {
                if (recursive_inner(new_path, depth + 1)) exit(errno);
                exit(0);
            }
        }
    }

    if (errno != 0) {
        perror("read dir");
        return errno;
    }

    if (closedir(cur_dir)) {
        perror("close dir");
        return errno;
    }

    return 0;
}

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Invalid number of args\n");
        return 1;
    }

    struct stat status;

    if (stat(args[1], &status)) {
        perror("stat error");
        return errno;
    }

    if (S_ISDIR(status.st_mode)) {
        recursive_inner(args[1], 0);
    }
}
