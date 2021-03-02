/*
*	Example of threads in action
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

int * retVal;

void *rot(void *i) {
	int creationNum = *(int*)i;
	
	retVal[creationNum] = creationNum*creationNum;
	printf("\n\t In thread PID: %d ; TID: %lu.; i*i: %d", getpid(), (unsigned long) pthread_self(),  creationNum*creationNum);
	pthread_exit((void*)retVal);	// no termination code
}

int main() {
	int i;	// thread counter
	pthread_t ids[NTHREADS];	// storage of (system) Thread Identifiers
	int creationNums[NTHREADS];
	void ** retValm = malloc(sizeof(void*));
	retVal = malloc(3*sizeof(int));

	setbuf (stdout, NULL);	// only for debugging
	printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(), (unsigned long) pthread_self());

	// new threads creation
	for(i=0; i<NTHREADS; i++) {
		creationNums[i] = i;
		if (pthread_create(&ids[i], NULL, rot, &creationNums[i]) != 0) {
			perror(NULL);
			exit(-1);	// here, we decided to end process
		} else
			printf("\nNew thread %d ; TID: %lu.", i, (unsigned long) ids[i]);
	
	}
	// wait for finishing of created threads
	for(i=0; i<NTHREADS; i++) {
		pthread_join(ids[i], retValm);	// Note: threads give no termination code

		printf("\nTermination of thread %d: %lu. Returned %d", i, (unsigned long)ids[i], (*(int**)retValm)[i]);
	}

	free(retVal);
	free(retValm);

	printf("\n");
	pthread_exit(NULL);	// here, not really necessary...
	return 0;	// will not run this!
}
