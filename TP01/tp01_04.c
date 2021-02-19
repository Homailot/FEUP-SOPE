#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(void) {
    char buffer[10];

    read(STDIN_FILENO, buffer, 10);
    char * newLine = strchr(buffer, '\n');
    if(newLine - buffer < 9) *(newLine+1) = '\0';

    printf("%s",buffer);
}