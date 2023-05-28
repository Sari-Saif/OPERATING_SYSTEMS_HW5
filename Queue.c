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


    queue->head= NULL;
    queue->tail = NULL;
    queue->count = 0;

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
    if (queue->tail == NULL)
    {
        queue->head= node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
   
    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->cond);
}

void *queue_pop(Queue *queue)
{
    pthread_mutex_lock(&queue->mutex);
    while (queue->head== NULL)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    Node *node = queue->front;
    void *data = node->data;
    queue->head= node->next;
    if (queue->head== NULL)
    {
        queue->tail = NULL;
    }
    
    free(node);
    pthread_mutex_unlock(&queue->mutex);
    return data;
}
