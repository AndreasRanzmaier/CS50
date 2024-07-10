#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void)
{
    for(int i = 0; i < 100; i++)
    {
        int r = (rand() % 2)+ 2;
        printf("%i\n", r);
    }
    return 0;
}