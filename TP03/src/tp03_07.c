
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCOUNT 100000
uint32_t count;
// pthread_mutex_t mutex;

// void* thr_fun(void* arg) {
//     pthread_mutex_lock(&mutex);
//     while (count < MAXCOUNT) {
//         printf("\n%u , thread %lu\n", count, pthread_self());
//         count++;
//         pthread_mutex_unlock(&mutex);
//         pthread_mutex_lock(&mutex);
//     }
//     pthread_mutex_unlock(&mutex);

//     printf("\nEND thread %lu!\n", pthread_self());
//     return (NULL);
// }

// int main(int argc, char* argv[]) {
//     pthread_t* pthreads;
//     int n_threads;

//     if (argc < 2) {
//         exit(EINVAL);
//     }

//     setbuf(stdout, NULL);
//     n_threads = atoi(argv[1]);
//     pthreads = malloc(sizeof(pthread_t) * n_threads);
//     if(pthread_mutex_init(&mutex, NULL)) {
//         perror("mutex");
//         exit(errno);
//     }

//     for (int i = 0; i < n_threads; i++) {
//         if (pthread_create(&pthreads[i], NULL, thr_fun, NULL)) {
//             perror("error thread create");
//             exit(errno);
//         }
//     }

//     for (int i = 0; i < n_threads; i++) {
//         pthread_join(pthreads[i], NULL);
//     }

//     printf("END\n");

//     return 0;
// }

pthread_mutex_t mutex;

void* routine(void* arg) {
    while (count < MAXCOUNT) {
        pthread_mutex_lock(&mutex);
        printf("\n%d", count);
        count++;
        pthread_mutex_unlock(&mutex);
    }

    printf("\nEND thread %lu!\n", (unsigned long)pthread_self());
    return NULL;
}

void cleanup() { pthread_mutex_destroy(&mutex); }

int main(int argc, char* argv[]) {
    pthread_t* pthreads;
    int n_threads;

    if (argc < 2) {
        exit(EINVAL);
    }

    count = 0;
    setbuf(stdout, NULL);
    n_threads = atoi(argv[1]);
    pthreads = malloc(sizeof(pthread_t) * n_threads);
    if (pthreads == NULL) {
        perror(NULL);
        exit(1);
    }

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror(NULL);
        exit(1);
    }
    atexit(cleanup);

    for (int i = 0; i < n_threads; i++) {
        if (pthread_create(&pthreads[i], NULL, routine, NULL) != 0) {
            perror(NULL);
            exit(1);
        }
    }

    for (int i = 0; i < n_threads; i++) pthread_join(pthreads[i], NULL);

    printf("\nEND!\n");
    pthread_exit(0);
}