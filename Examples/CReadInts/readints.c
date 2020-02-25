#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// #include <ctype>
#include <string.h>

#define BUFFSIZE 128

bool is_int(char *input)
{
    int length = strlen(input);
    if (length == 0)
        return false;

    if (*input != '-' && (*input < '0' || *input > '9'))
        return false;
    else if (*input == '-' && length < 2)
        return false;

    for (int i = 0; i < length && *(++input) != '\0'; i++)
        if (*input < '0' || *input > '9')
            return false;
    return true;
}

bool get_integer(char *input, int *value)
{
    long long long_long_i;
    if (sscanf(input, "%lld", &long_long_i) == 1)
    {
        *value = (int)long_long_i;
        if (long_long_i != (long long)*value)
        {
            fprintf(stderr, "Error: Integer overflow with '%s'.\n", input);
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return EXIT_FAILURE;
    char buffer[128];
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        puts("Error: Cannot open file.");
        return EXIT_FAILURE;
    }
    while (fgets(buffer, BUFFSIZE, fp) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';
        if (is_int(buffer))
        {
            int val;
            if (get_integer(buffer, &val))
            {
                printf("%d", val);
            }
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}