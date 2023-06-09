/***
 *  tutorial :
 *  https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "AObject.h"

#define FALSE 0
#define TRUE 1

// global's
AObject *ao_0 = NULL;
AObject *ao_1 = NULL;
AObject *ao_2 = NULL;
AObject *ao_3 = NULL;

/**
 * will initialize the random generator with the given seed and then generate N numbers of 6 digits each (possible 3 + 3) -
 * with the help of .rand
 * He will transfer one by one to the AO after him, with differences of one thousandth of a second - (1)
 */
int opreation1(void *value)
{

    int *num = (int *)value;
    *num = rand() % 900000 + 100000; // random
    queue_push(get_Queue(ao_1), num);
    usleep(1000000); // Sleep for 1 second (1,000,000 microseconds)
    return 0;
}

/**
 * will print the number, check if the number is prime, and print true or false accordingly.
 * will add to number 11 and transfer it to the next AO
 */
int opreation2(void *value)
{
    int *num = (int *)value;
    int data = *num;

    printf("%d", data);
    printf("\n");

    if (isPrime(*num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    *num += 11;
    queue_push(get_Queue(ao_2), num);

    return 0;
}

/* like operation 2 just decrease 13 */

int opreation3(void *value)
{
    int *num = (int *)value;
    int data = *num;

    printf("%d", data);
    printf("\n");

    if (isPrime(*num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    *num -= 13;
    queue_push(get_Queue(ao_3), num);

    return 0;
}

/**
 * The fourth AO will print the received number, add to the number 2, and print the new number.
 * If you did everything correctly, the last number will be equal to the first
 */
int opreation4(void *value)
{
    int *num = (int *)value;
    printf("%d\n", *num);

    *num += 2;
    printf("%d\n", *num);
    return 0;
}

/*
    push and operate
*/
void operateAll()
{
    queue_push(get_Queue(ao_0), NULL);
    queue_push(get_Queue(ao_1), NULL);
    queue_push(get_Queue(ao_2), NULL);
    queue_push(get_Queue(ao_3), NULL);
}

/*
    stop all operation's(Active object's)
*/
void stopAll()
{
    stopAObject(ao_0);
    stopAObject(ao_1);
    stopAObject(ao_2);
    stopAObject(ao_3);
}

int main(int argc, char *argv[])
{
    // parameter's for random
    int N;
    long seed;

    // the usage format
    if (argc < 2 || argc > 3)
    {
        printf("Usage: pipeline N [seed]\n");
        return 0;
    }
    // number of mission's
    N = atoi(argv[1]);
    if (argc == 3)
    {
        seed = atol(argv[2]);
    }
    seed = time(NULL);
    srand(seed);

    // Create the ActiveObjects for each opreation init and modify thim
    ao_0 = createAObject(opreation1);
    ao_1 = createAObject(opreation2);
    ao_2 = createAObject(opreation3);
    ao_3 = createAObject(opreation4);

    int i = 0;
    while (i < N)
    {
        int *num = malloc(sizeof(int));
        if (num == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
        // push to queue what you extract from the Active object and modify the relevant data
        queue_push(get_Queue(ao_0), num);
        usleep(1000000); // sleep for 1 sec what ineeded in task read the readme.md
        printf("\n");

        i++;
    }
    // need to clean after it's done
    operateAll();
    // stop all active objects because it's done
    stopAll();

    return 0;
}