#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strdup(const char *s)
{
    if (s == NULL)
        return NULL;
    size_t len = strlen(s) + 1; // +1 to store \n, which isn't given by strlen

    // Malloc returns a void*, because malloc is only allocating
    // memory. It doesn't know it's an array of characters
    char *copy = (char *)malloc(len * sizeof(char));
    if (copy == NULL)
        return NULL;
    /*
        char *t = copy;
        while (*s) {
            *t++ = *s++;
        }
        return copy;  
    */
    return (char *)memcpy(copy, s, len);
}

int main()
{
    char name[128];
    printf("What is your name? ");
    scanf("%s", name);

    printf("Hello, %s!\n", name);
    printf("Your name has %ld characters.\n", strlen(name));

    // copying a string, string duplicate in stl
    char *copy = my_strdup(name);
    printf("Hello, %s!\n", name);
    printf("Your name has %ld characters.\n", strlen(*copy));
}