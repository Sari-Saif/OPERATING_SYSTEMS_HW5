#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdlib.h>

typedef struct Node
{
    void *data;
    struct Node *next;
}Node;

typedef struct
{
    // This pointer represents the front of the queue, pointing to the first node
    Node *front;
    // pointing to the last node in the queue.
    Node *rear;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue;

Queue *init();
void queue_push(Queue *q, void *data);
void *queue_pop(Queue *q);
void queue_destroy(Queue *q);

#endif