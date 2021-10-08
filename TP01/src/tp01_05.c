#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[], char * env[]) {
    printf("---------------Command arguments: \n\n");
    int i = 0;

    for(; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    i=0;

    printf("\n\n ---- ALTERNATIVELY WITH GETENV\n\n");

    for(int i = 0; i < argc; i++) {
        printf("%s=%s\n", argv[i] , getenv(argv[i]));
    }

    printf("\n\n--------------Environment variables: \n\n");
    char * eqPointer;

    while(env[i] != NULL) {
        eqPointer = strchr(env[i], '=');
        *eqPointer = 0;
        for(int j = 0; j < argc; j++) {
            if(strcmp(env[i], argv[j]) == 0) {
                printf("%s\n", eqPointer+1);
            }
        }
        i++;
    }
}

//export DIR1='123-testing'