// #include "solution.h"

#include <stddef.h>
int stringStat(const char *string, size_t multiplier, int *count)
{
    int it = 0;
    while (*(string+it)!='\0')
    {
        it++;
    }
    *(count) += 1;
    return it * multiplier;
}
