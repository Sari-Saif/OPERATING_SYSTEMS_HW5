#include "Queue.h"

/* init the queue by default parameters and make it safe-thread*/
Queue *init()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    // there need to check that
    if (queue == NULL)
    {
        // we cant to continue and init parameters
        return NULL;
    }

    queue->front = NULL;
    queue->rear = NULL;
    
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return queue;
}

void queue_push(Queue *queue, void *data)
{

    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    pthread_mutex_lock(&queue->mutex);
    if (queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->count++;
    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->cond);
}

void *queue_pop(Queue *queue)
{
    pthread_mutex_lock(&queue->mutex);
    while (queue->front == NULL)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    Node *node = queue->front;
    void *data = node->data;
    queue->front = node->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    queue->count--;
    free(node);
    pthread_mutex_unlock(&queue->mutex);
    return data;
}
