#include <stdio.h>
#include <stdlib.h>

int global; /* Uninitialized variable stored in bss*/
int global_init = 10;
const int global_const_init = 13;

int main(void)
{
    static int stat; /* Uninitialized static variable stored in bss */
    static int stat_init = 10;
    int j = 10;

    int * ints = malloc(sizeof(int)*5);

    printf("global=  %p\n", &global);
    printf("global_init=  %p\n", &global_init);
    printf("global_const_init=  %p\n", &global_const_init);
    printf("stat=  %p\n", &stat);
    printf("stat_init=  %p\n", &stat_init);
    printf("j=  %p\n", &j);
    printf("ints 0=  %p\n", ints);
    printf("ints 1=  %p\n", &ints[1]);

    free(ints);

    return 0;
}
