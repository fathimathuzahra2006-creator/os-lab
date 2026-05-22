#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource, readTry, rmutex, wmutex;

int readcount = 0, writecount = 0;
int data = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&readTry);
    sem_wait(&rmutex);

    readcount++;

    if (readcount == 1)
        sem_wait(&resource);

    sem_post(&rmutex);
    sem_post(&readTry);

    printf("Reader %d is reading data = %d\n", id, data);
    sleep(1);

    sem_wait(&rmutex);

    readcount--;

    if (readcount == 0)
        sem_post(&resource);

    sem_post(&rmutex);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&wmutex);

    writecount++;

    if (writecount == 1)
        sem_wait(&readTry);

    sem_post(&wmutex);

    sem_wait(&resource);

    data++;
    printf("Writer %d is writing data = %d\n", id, data);
    sleep(1);

    sem_post(&resource);

    sem_wait(&wmutex);

    writecount--;

    if (writecount == 0)
        sem_post(&readTry);

    sem_post(&wmutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t r[5], w[2];

    int rid[5] = {1, 2, 3, 4, 5};
    int wid[2] = {1, 2};

    sem_init(&resource, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&resource);
    sem_destroy(&readTry);
    sem_destroy(&rmutex);
    sem_destroy(&wmutex);

    return 0;
}