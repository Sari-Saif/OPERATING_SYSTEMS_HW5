#include <stdio.h>
#include <stdlib.h>
#include "AObject.h"

void *run(void *arg)
{
    AObject *ao = (AObject *)arg;
    void *task = NULL;

    do
    {
        task = queue_pop(ao->queue);
        if (task != NULL)
        {
            ao->func(task);
        }
    } while (task != NULL);

    return NULL;
}

AObject *createAObject(int (*func)(void *))
{
    AObject *ao = (AObject *)malloc(sizeof(AObject));
    if (ao == NULL)
    {
        return NULL;
    }

    ao->queue = init(); // create queue
    ao->func = func;
    ao->its_on = 1; // on

    if (pthread_create(&ao->thread, NULL, run, ao) != 0)
    {
        // delete to avoid leak memory
        free(ao->queue);
        free(ao);
        return NULL;
    }

    return ao;
}

void stopAObject(AObject *activeObject)
{
    activeObject->its_on = 0;
    pthread_join(activeObject->thread, NULL);
    queue_destroy(activeObject->queue);
    free(activeObject);
}

Queue *get_Queue(AObject *activeObject)
{
    return activeObject->queue;
}
