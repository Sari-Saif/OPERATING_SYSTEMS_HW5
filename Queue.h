/*
    implemention goal's:
    Queue in a crowded environment.
    The queue should have Miotex protections and also allow waiting for the member in the queue without busy waiting
*/
#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct
{
    // This pointer represents the front of the queue, pointing to the first node
    Node *head;
    // pointing to the last node in the queue.
    Node *tail;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue;

Queue *init();

/*
function adds a node to the tail of the queue.
It creates a new node, sets its data to the input data, and adds it to the end of the queue.
If the queue is empty, it sets both the front and rear pointers to the new node.
signals the condition variable to wake up any threads waiting on the queue.
*/
void queue_push(Queue *q, void *data);

/*
function removes a node from the head of the queue (FIFO). If the queue is empty,
 it waits on the condition variable until there is a node in the queue. Once a node is available,
 it removes it from the head of the queue, decrements the count of nodes in the queue,
 and signals the condition variable to wake up any threads waiting on the queue.
 It then returns the data from the removed node.
*/
void *queue_pop(Queue *q);

/**
 * lock the mutex to ensure no other threads are accessing the queue during the destruction process.
 * iterate through the nodes in the queue, freeing the memory allocated for each node's data and the node itself.
 * Unlock the mutex and destroy it.
 * destroy the condition variable.
 * finally, set the head and tail pointers to NULL.
 */
void queue_destroy(Queue *q);

/*
    function  get unsigned int and return if prime or not peime
 */
int isPrime(unsigned int n);

#endif