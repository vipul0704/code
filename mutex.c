#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int itemCount = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *producer(void *arg);
void *consumer(void *arg);
int main() {
    pthread_t producerThread, consumerThread;
    if (pthread_create(&producerThread, NULL, producer, NULL) != 0) {
        fprintf(stderr, "Error: Unable to create producer thread.\n");
        return 1;
    }
    if (pthread_create(&consumerThread, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Error: Unable to create consumer thread.\n");
        return 1;
    }
    if (pthread_join(producerThread, NULL) != 0) {
        fprintf(stderr, "Error: Unable to join producer thread.\n");
        return 1;
    }
    if (pthread_join(consumerThread, NULL) != 0) {
        fprintf(stderr, "Error: Unable to join consumer thread.\n");
        return 1;
    }
    return 0;
}

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1);
        pthread_mutex_lock(&mutex);
        if (itemCount < BUFFER_SIZE) {
            buffer[itemCount++] = i;
            printf("Produced: %d\n", i);
        } else {
            printf("Buffer is full. Producer is waiting.\n");
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}
void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1);
        pthread_mutex_lock(&mutex);
        if (itemCount > 0) {
            int item = buffer[--itemCount];
            printf("Consumed: %d\n", item);
        } else {
            printf("Buffer is empty. Consumer is waiting.\n");
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}