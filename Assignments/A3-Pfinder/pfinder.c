/*******************************************************************************
 * Name        : pfinder.c
 * Author      : Ryan Hartman
 * Date        : 2/21/2020
 * Description : Recursively searches a directory for a file or directory with a specific
 *             : permission string
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <getopt.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#define BUFSIZE 128

void find_files(char *path, unsigned int perms);
unsigned int parse_permissions(char *perms);
void print_usage(char *cmd);

int main(int argc, char *argv[])
{
    int d_flag = 0, h_flag = 0, p_flag = 0, opt, perms;
    char path[PATH_MAX], rel_path[PATH_MAX], permsString[10];
    while ((opt = getopt(argc, argv, ":d:p:h")) != -1)
    {
        switch (opt)
        {
        case 'd':
            d_flag = 1;
            strcpy(rel_path, optarg);
            break;
        case 'p':
            if (strlen(optarg) == 9)
            {
                p_flag = 1;
                strcpy(permsString, optarg);
                permsString[9] = '\0';
                perms = parse_permissions(permsString);
            }
            else
            {
                fprintf(stderr, "Error: Permissions string '%s' is invalid.", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 'h':
            h_flag = 1;
            break;
        case '?':
            fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
            return EXIT_FAILURE;
        }
    }
    if (h_flag == 1)
    {
        print_usage(argv[0]);
        return EXIT_SUCCESS;
    }
    else if (!d_flag)
    {
        fprintf(stderr, "Error: Required argument -d <directory> not found.");
        return EXIT_FAILURE;
    }
    else if (!p_flag)
    {
        fprintf(stderr, "Error: Required argument -p <permissions string> not found.");
        return EXIT_FAILURE;
    }
    d_flag = h_flag + p_flag;
    h_flag = d_flag + p_flag;
    if (realpath(rel_path, path) == NULL)
    {
        fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", rel_path, strerror(errno));
        return EXIT_FAILURE;
    }
    perms = 0;
    find_files(path, perms);

    return EXIT_SUCCESS;
}

void find_files(char *path, unsigned int perms)
{
    DIR *dir;
    if ((dir = opendir(path)) == NULL)
    {
        fprintf(stderr, "Error: Cannot open directory '%s'. %s.\n", path, strerror(errno));
        return;
    }
    struct dirent *entry;
    struct stat sb;
    char full_filename[PATH_MAX];
    size_t pathlen = 0;
    full_filename[0] = '\0';
    if (strcmp(path, "/"))
    {
        // If path is not the root - /, then....
        strncpy(full_filename, path, PATH_MAX - 1);
    }
    pathlen = strlen(full_filename) + 1;
    // Add 1 because we're going to add a /.

    full_filename[pathlen - 1] = '/';
    full_filename[pathlen] = '\0';

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        strncpy(full_filename + pathlen, entry->d_name, PATH_MAX - pathlen);
        if (lstat(full_filename, &sb) < 0)
        {
            fprintf(stderr, "Error: Cannot stat file '%s'. %s.\n", full_filename, strerror(errno));
            continue;
        }

        if (perms == (sb.st_mode & 511))
            printf("%s\n", full_filename);

        if (entry->d_type == DT_DIR)
            find_files(full_filename, perms);
    }
    closedir(dir);
}

unsigned int parse_permissions(char *permString)
{
    char valid_perms[3] = {'x', 'w', 'r'};
    unsigned int perms = 0;
    char *cur = permString;
    for (int i = 6; i >= 0; i -= 3)
    {
        for (int j = 2; j >= 0; j--)
        {
            if (*(cur) == valid_perms[j] || *(cur) == '-')
            {
                // printf("Read a %c, flipping bit %d to a %d.\n", *(cur), i + j, *(cur) != '-');
                perms |= (*(cur) != '-') << (i + j);
                cur++;
            }
            else
            {
                fprintf(stderr, "Error: Permissions string '%s' is invalid.", permString);
                exit(EXIT_FAILURE);
            }
        }
    }
    // printf("Total: %d\n", perms);
    return perms;
}

void print_usage(char *cmd)
{
    printf("Usage: %s -d <directory> -p <permissions string> [-h]\n", cmd);
}