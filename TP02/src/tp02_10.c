/*
 *	Example of threads in action
 */
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NTHREADS 2

bool taskFinished[NTHREADS];

typedef struct arg {
    char message[15];
    int order;
} arg_t;

void* rot(void* i) {
    arg_t* arg = (arg_t*)i;

    while (arg->order != 0 && !taskFinished[arg->order - 1]);

    printf("%s", arg->message);

    taskFinished[arg->order] = true;

    return NULL;
}

int main() {
    int i;                    // thread counter
    pthread_t ids[NTHREADS];  // storage of (system) Thread Identifiers
    arg_t args[NTHREADS];
    strcpy(args[0].message, "Operating ");
    strcpy(args[1].message, "Systems\n");
    args[0].order = 0;
    args[1].order = 1;

    int creationNums[NTHREADS];

    setbuf(stdout, NULL);  // only for debugging

    // new threads creation
    for (i = 0; i < NTHREADS; i++) {
        creationNums[i] = i;
        taskFinished[i] = false;
        if (pthread_create(&ids[i], NULL, rot, &args[i]) != 0) {
            perror(NULL);
            exit(-1);  // here, we decided to end process
        }
    }
    // wait for finishing of created threads
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(ids[i], NULL);  // Note: threads give no termination code
    }
    return 0;  // will not run this!
}

// ps -eLf --- gives info on threads
