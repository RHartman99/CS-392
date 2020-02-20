/*******************************************************************************
 * Name        : sort.c
 * Author      : Ryan Hartman
 * Date        : 2/21/2020
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN 64 // Not including '\0'
#define MAX_ELEMENTS 1024

typedef enum
{
  STRING,
  INT,
  DOUBLE
} elem_t;

/**
 * Basic structure of sort.c:
 *
 * Parses args with getopt.
 * Opens input file for reading.
 * Allocates space in a char** for at least MAX_ELEMENTS strings to be stored,
 * where MAX_ELEMENTS is 1024.
 * Reads in the file
 * - For each line, allocates space in each index of the char** to store the
 *   line.
 * Closes the file, after reading in all the lines.
 * Calls quicksort based on type (int, double, string) supplied on the command
 * line.
 * Frees all data.
 * Ensures there are no memory leaks with valgrind. 
 */

void print_usage(char *cmd)
{
  printf("Usage: %s [-i|-d] [filename]\n", cmd);
  printf("    -i: Specifies the file contains ints.\n");
  printf("    -d: Specifies the file contains doubles.\n");
  printf("    filename: The file to sort.\n");
  printf("    No flags defaults to sorting strings.\n");
}

int main(int argc, char **argv)
{
  int i_flag = 0, d_flag = 0, opt;
  while ((opt = getopt(argc, argv, ":id")) != -1)
  {
    switch (opt)
    {
    case 'i':
      i_flag = 1;
      break;
    case 'd':
      d_flag = 1;
      break;
    case '?':
      fprintf(stderr, "Error: Unknown option '%c' received.\n", optopt);
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
  }

  if (i_flag + d_flag > 1)
  {
    fprintf(stderr, "Error: Too many options enabled.\n");
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  FILE *fp;
  if (optind >= argc)
  {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }
  else if ((fp = fopen(argv[optind], "r")) == NULL)
  {
    fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno));
    return EXIT_FAILURE;
  }
  char **strings = (char **)malloc(MAX_ELEMENTS * sizeof(char *));
  char **cur = strings;
  char *buf = (char *)malloc(MAX_STRLEN * sizeof(char) + 1);
  int length = 0;
  while (fgets(buf, MAX_STRLEN, fp) != NULL)
  {
    *(buf + strlen(buf)) = '\0';
    *cur = (char *)malloc(strlen(buf) * sizeof(char) + 1);
    *cur = buf;
    printf("%s", *cur);
    length++;
    cur++;
  }
  fclose(fp);

  if (i_flag == 1)
  {
  }
  else if (d_flag == 1)
  {
  }
  else
  {
  }

  return EXIT_SUCCESS;
}
