#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

/* checked in online compiler c++ 11 */
int isPrime(unsigned int n)
{
    // if its even the non need to continue
    if (n % 2 == 0 || n == 1)
    {
        return FALSE;
    }

    unsigned int Sq = sqrt(n);
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

int main()
{
    int v = isPrime(17);
    printf("%d", v);

    return 0;
}