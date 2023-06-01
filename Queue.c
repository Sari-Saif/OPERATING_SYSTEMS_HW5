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

void *queue_pop(Queue *queue)
{
    pthread_mutex_lock(&queue->mutex);
    while (queue->head == NULL)
    {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    Node *node = queue->head;
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

void queue_destroy(Queue *q)
{
    // lock the mutex
    pthread_mutex_lock(&q->mutex);

    // iterate through the nodes and free the memory
    Node *current = q->head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    // Unlock the mutex and destroy it
    pthread_mutex_unlock(&q->mutex);
    pthread_mutex_destroy(&q->mutex);

    // Destroy the condition variable
    pthread_cond_destroy(&q->cond);

    // Set the head and tail pointers to NULL
    q->head = NULL;
    q->tail = NULL;
}

int isPrime(unsigned int n)
{
    // if its even the non need to continue
    if (n % 2 == 0 || n == 1)
    {
        return FALSE;
    }

    // get the sqrt of input number
    unsigned int Sq = pow(n, 0.5);
    // first odd number
    unsigned int i = 3;
    // Check divisibility with odd numbers up to the square root
    while (i <= Sq)
    {
        if (n % i == 0)
        {
            return FALSE;
        }
        i += 2;
    }
    return TRUE;
}