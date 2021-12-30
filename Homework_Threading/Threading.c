#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define sizeOfArray 4
#define threadsNumber 3

    int *arr;
    int globalIndex = 0;
    int sum = 0;
    pthread_mutex_t mutex;

    void * routine(void *arg) {
        int localIndex, partialSum = 0;
        do {
            pthread_mutex_lock( & mutex);
            localIndex = globalIndex;
            globalIndex++;
            pthread_mutex_unlock( & mutex);

            if (localIndex < sizeOfArray)
                partialSum += arr[localIndex];
        }
        while (localIndex < sizeOfArray);
        pthread_mutex_lock( & mutex);
        sum += partialSum;
        pthread_mutex_unlock( & mutex);

        return 0;
    }

    int* generateArray() {
        static int arrLocal[ sizeOfArray];
        for (int i = 0; i < sizeOfArray; ++i) {
             arrLocal[i] = rand() % 10;
             printf("%d\n",arrLocal[i]);
        }
        return arrLocal;
    }

    int main() {
        int i;
        pthread_t thread_x[threadsNumber];
        pthread_mutex_init( & mutex, NULL);

        arr = generateArray();
        for (i = 0; i < threadsNumber; i++)
            pthread_create( & thread_x[i], NULL, &routine, NULL);

        for (i = 0; i < threadsNumber; i++)
            pthread_join(thread_x[i], NULL);

        printf("The sum of 1 to %d is %d\n", sizeOfArray, sum);
    }