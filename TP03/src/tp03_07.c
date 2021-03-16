#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAXCOUNT 100000
uint32_t count;
pthread_mutex_t mutex;

void* thr_fun(void* arg) {
    pthread_mutex_lock(&mutex);
    while (count < MAXCOUNT) {
        printf("\n%u , thread %lu\n", count, pthread_self());
        count++;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("\nEND thread %lu!\n", pthread_self());
    return (NULL);
}

int main(int argc, char* argv[]) {
    pthread_t* pthreads;
    int n_threads;

    if (argc < 2) {
        exit(EINVAL);
    }

    setbuf(stdout, NULL);
    n_threads = atoi(argv[1]);
    pthreads = malloc(sizeof(pthread_t) * n_threads);
    if(pthread_mutex_init(&mutex, NULL)) {
        perror("mutex");
        exit(errno);
    }

    for (int i = 0; i < n_threads; i++) {
        if (pthread_create(&pthreads[i], NULL, thr_fun, NULL)) {
            perror("error thread create");
            exit(errno);
        }
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(pthreads[i], NULL);
    }

    printf("END\n");

    return 0;
}