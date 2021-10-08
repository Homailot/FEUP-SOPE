/*
 *	Example of threads in action
 */
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NTHREADS 3

// void* rot(void* i) {
//     int creationNum = *(int*)i;

//     int* retVal = malloc(sizeof(int));
//     *retVal = creationNum * creationNum;

//     printf("\n\t In thread PID: %d ; TID: %lu.; i*i: %d", getpid(),
//            (unsigned long)pthread_self(), creationNum * creationNum);
//     pthread_exit((void*)retVal);  // no termination code
// }

void* rot(void* i) {
    int i_val = *((int*)i);
    free(i);

    int ret = i_val * i_val;
    int* ret_p = malloc(sizeof(ret));
    if(ret_p == NULL) return NULL;

    *ret_p = ret;

    return ret_p;
}

void cleanup() {
    printf("goodbye\n");
}

int main() {
    // int i;                    // thread counter
    // pthread_t ids[NTHREADS];  // storage of (system) Thread Identifiers
    // int creationNums[NTHREADS];
    // void** retValm = malloc(sizeof(void*));

    // setbuf(stdout, NULL);  // only for debugging
    // printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(),
    //        (unsigned long)pthread_self());

    // // new threads creation
    // for (i = 0; i < NTHREADS; i++) {
    //     creationNums[i] = i;
    //     if (pthread_create(&ids[i], NULL, rot, &creationNums[i]) != 0) {
    //         perror(NULL);
    //         exit(-1);  // here, we decided to end process
    //     } else
    //         printf("\nNew thread %d ; TID: %lu.", i, (unsigned long)ids[i]);
    // }
    // // wait for finishing of created threads
    // for (i = 0; i < NTHREADS; i++) {
    //     pthread_join(ids[i],
    //                  retValm);  // Note: threads give no termination code

    //     printf("\nTermination of thread %d: %lu. Returned %d", i,
    //            (unsigned long)ids[i], (**(int**)retValm));

    //     free(retValm[0]);
    // }

    // free(retValm);

    // printf("\n");
    // return 0;  // will not run this!

    atexit(cleanup);

    int i;
    pthread_t threads[NTHREADS];
    pthread_attr_t attr;

    printf("%lu\n", strlen("a"));

    pthread_attr_init(&attr);

    for(i=0; i < NTHREADS; i++) {
        int* arg = malloc(sizeof(int));
        if(arg == NULL) exit(1);
        *arg = i;

        if(pthread_create(&threads[i], &attr, rot, arg) != 0) {
            threads[i] = -1;
        }
    }

    for(i=0; i<NTHREADS;i++) {
        void* ret;
        if(threads[i]!=-1) {
            pthread_join(threads[i], &ret);
            if(ret == NULL) continue;

            int ret_val = *((int*)ret);
            free(ret);

            printf("THREAD I= %d; RET= %d\n", i, ret_val);
        }
    }

    pthread_attr_destroy(&attr);

    pthread_exit(0);
}

// ps -eLf --- gives info on threads
