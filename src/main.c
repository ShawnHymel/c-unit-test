#include <stdio.h>
#include "average.h"

int main()
{
    float array[] = {-1.0, 0.0, 1.0, 2.0, 3.0};
    float avg = average(array, 5);
    printf("Average: %f\r\n", avg);
    
    return 0;
}