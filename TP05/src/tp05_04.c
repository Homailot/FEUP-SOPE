#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main() {
    // i.
    printf("Number of clock ticks in a second: %ld. Clock right now %uld\n",
           CLOCKS_PER_SEC, (uint32_t)clock());

    // ii.
    time_t zero_time = 0;
    printf("The epoch time is: %s\n", ctime(&zero_time));

    // iii.
    // ?
    return 0;
}
