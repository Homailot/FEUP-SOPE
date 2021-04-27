// Turn off echoing on screen of keyboard characters: example program.

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char c;
    struct termios tms, tms_ini;

    printf("\nTo end, press [Enter]\n");

    tcgetattr(STDIN_FILENO, &tms_ini);  // read console's configuration
    tms = tms_ini;


    tms.c_lflag |= ECHOE | ICANON;                    // inhibit char echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &tms);  // set new configuration

    do {
        if (read(STDIN_FILENO, &c, 1) != 1) perror("read failed");
    } while (c != '\n');  // wait for [ENTER]

    tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);  // reset configuration
    // experiment this program with the above line commented! ;-)
    printf("\nInitial console configuration has been reset!\n");

    return 0;
}  // main()
