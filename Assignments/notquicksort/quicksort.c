#include <stdio.h>
#include <string.h>
#include "quicksort.h"

#define MAX_EL 1024
#define MAX_CH 64

int get_integer(char *input)
{
    int val;
    sscanf(input, "%d", &val);
    return val;
}

double get_double(char *input)
{
    double val;
    sscanf(input, "%lf", &val);
    return val;
}

void convert_int(char *arr[], int *convert_to, int size)
{
    printf("%s", arr[0]);
    for (int i = 0; i < size; i++)
    {
        *(convert_to++) = i + 1;
    }
}

void convert_double(char **arr, double *convert_to, int size)
{
    *(convert_to++) = get_integer(*(arr++));
}

int lomuto_partition(void *arr, int left, int right, int type)
{
    if (type == 0)
    {
        arr = (int)arr;
    }
    else if (type == 1)
    {
        arr = (double)arr;
    }
    else if (type == 2)
    {
        arr = (char)arr;
    }
    int p = arr + left;
    int s = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (arr < p)
        {
            s++;
            // swap(array[s], array[i]);
        }
    }
    // swap(array[left], array[s]);
    return s;
}
