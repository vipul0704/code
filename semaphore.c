#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int itemCount = 0;
sem_t empty, full, mutex;
void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1);
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[itemCount++] = i;
        printf("Produced: %d\n", i);
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}
void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1);
        sem_wait(&full);
        sem_wait(&mutex);
        printf("Consumed: %d\n", buffer[--itemCount]);
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}
int main() {
    pthread_t producerThread, consumerThread;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}