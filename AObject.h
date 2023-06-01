#ifndef AO_H
#define AO_H

#include <pthread.h>
#include "Queue.h"

typedef struct
{
    Queue *queue;
    int (*func)(void *); // call for each queue properties
    int its_on;          // flage if active
    pthread_t thread;

} AObject;

void stopAObject(AObject *activeObject);
AObject *createAObject(int (*func)(void *));
Queue *get_Queue(AObject *activObject);

#endif // AO_H