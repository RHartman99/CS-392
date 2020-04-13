#include <errno.h>
#include <limits.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define BRIGHTBLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"
#define BUFSIZE 256

int main()
{
    char path_buf[PATH_MAX];
    char buffer[BUFSIZE];
    char *path;
    do
    {
        if ((path = getcwd(path_buf, PATH_MAX)) == NULL)
        {
            fprintf(stderr,
                    "Error: Cannot get current work directory. %s.\n",
                    strerror(errno));
            return EXIT_FAILURE;
        }
        printf("[%s%s%s]$ ", BRIGHTBLUE, path, DEFAULT);
        fflush(stdout);
        ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFSIZE);
        if (bytes_read > 0)
            buffer[bytes_read - 1] = '\0';

        if (bytes_read == 1)
            continue;

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        if (strncmp(buffer, "cd", 2) == 0)
        {
            printf("nigga\n");
        }

    } while (true);
    return EXIT_SUCCESS;
}