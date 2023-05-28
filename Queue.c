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

    queue->head = NULL;
    queue->tail = NULL;

    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return queue;
}
/*
function adds a node to the tail of the queue.
It creates a new node, sets its data to the input data, and adds it to the end of the queue.
If the queue is empty, it sets both the front and rear pointers to the new node.
signals the condition variable to wake up any threads waiting on the queue.
*/
void queue_push(Queue *queue, void *data)
{

    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    pthread_mutex_lock(&queue->mutex);
    if (queue->tail == NULL)
    {
        queue->head = node;
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
/*
function removes a node from the head of the queue (FIFO). If the queue is empty,
 it waits on the condition variable until there is a node in the queue. Once a node is available,
 it removes it from the head of the queue, decrements the count of nodes in the queue,
 and signals the condition variable to wake up any threads waiting on the queue.
 It then returns the data from the removed node.
*/
void *queue_pop(Queue *queue)
{
    pthread_mutex_lock(&queue->mutex);
    while (queue->head == NULL)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    Node *node = queue->front;
    void *data = node->data;
    queue->head = node->next;
    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }

    free(node);
    pthread_mutex_unlock(&queue->mutex);
    return data;
}
