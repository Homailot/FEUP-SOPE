/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE 20
#define MAX_ITER 100000
long iter;

pthread_mutex_t iter_mutex;
sem_t count_sem;

void* producer(void*);
void* consumer(void*);

void cleanup() {
    pthread_mutex_destroy(&iter_mutex);
    sem_destroy(&count_sem);
}

int main(int argc, char* argv[]) {
    pthread_t* ptid;
    int nthreads;
    int i;

    setbuf(stdout, NULL);
    if (argc < 2) {
        printf("\nUsage: %s #threads\n", argv[0]);
        exit(1);
    }

    nthreads = atoi(argv[1]);
    ptid = malloc(nthreads * sizeof(pthread_t));
    if (ptid == NULL) {
        perror("malloc");
        exit(2);
    }

    if (pthread_mutex_init(&iter_mutex, NULL)) {
        perror(NULL);
        exit(1);
    }

    if (sem_init(&count_sem, 0, BUF_SIZE)) {
        perror(NULL);
        exit(1);
    }
    atexit(cleanup);

    for (i = 0; i < nthreads; i++) {
        if (i % 2 == 0 && pthread_create(&ptid[i], NULL, producer, NULL) != 0) {
            perror("pthread_create");
            exit(3);
        } else if (i % 2 == 1 &&
                   pthread_create(&ptid[i], NULL, consumer, NULL) != 0) {
            perror("pthread_create");
            exit(3);
        }
    }

    for (i = 0; i < nthreads; i++) pthread_join(ptid[i], NULL);

    printf("\nEND!\n");
    return 0;
}

void* producer(void* arg) {
    while(true) {
        pthread_mutex_lock(&iter_mutex);
        if(iter >= MAX_ITER) {
            pthread_mutex_unlock(&iter_mutex);
            break;
        }

        int count;

        sem_getvalue(&count_sem, &count);

        if(count < BUF_SIZE) {
            sem_post(&count_sem);
            count++;
        }

        iter++;

        printf("PRODUCE :( COUNT= %d;ITER= %ld\n", count, iter);

        pthread_mutex_unlock(&iter_mutex);
    }

    printf("\nEND thread %lu!\n", (unsigned long)pthread_self());

    return (NULL);
}

void* consumer(void* arg) {
    while(true) {
        int count;
        sem_wait(&count_sem);

        pthread_mutex_lock(&iter_mutex);
        if(iter >= MAX_ITER) {
            pthread_mutex_unlock(&iter_mutex);
            break;
        }

        iter++;

        sem_getvalue(&count_sem, &count);
        printf("CONSUME :) COUNT= %d;ITER= %ld\n", count, iter);

        pthread_mutex_unlock(&iter_mutex);
    }

    printf("\nEND thread %lu!\n", (unsigned long)pthread_self());

    return (NULL);
}
