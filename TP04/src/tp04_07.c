#include <stdio.h>

int global = 10; /* Uninitialized variable stored in bss*/

int main(void)
{
    static int i = 100; /* Uninitialized static variable stored in bss */
    return 0;
}
