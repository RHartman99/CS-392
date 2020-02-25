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

void convert_to_ints(char **a, int *b, int length)
{
  for (int i = 0; i < length; i++)
  {
    int val;
    sscanf(*(a++), "%d", &val);
    *(b++) = val;
  }
}

void convert_to_dbls(char **a, double *b, int length)
{
  for (int i = 0; i < length; i++)
  {
    double val;
    sscanf(*(a++), "%lf", &val);
    *(b++) = val;
  }
}

void print_usage(char *cmd)
{
  printf("Usage: %s [-i|-d] [filename]\n", cmd);
  printf("    -i: Specifies the file contains ints.\n");
  printf("    -d: Specifies the file contains doubles.\n");
  printf("    filename: The file to sort.\n");
  printf("    No flags defaults to sorting strings.\n");
}

void print_array(void *arr, elem_t type, int length)
{
  int *int_arr = (int *)arr;
  double *dbl_arr = (double *)arr;
  char **str_arr = (char **)arr;
  for (int i = 0; i < length; i++)
  {
    if (type == STRING)
      printf("%s\n", *(str_arr++));
    else if (type == INT)
      printf("%d\n", *(int_arr++));
    else
      printf("%lf\n", *(dbl_arr++));
  }
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
      fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
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

  // Parse the file
  char **strings = (char **)malloc(MAX_ELEMENTS * sizeof(char *));
  char **cur = strings;
  char *buf = (char *)malloc(MAX_STRLEN * sizeof(char) + 2);
  int length = 0;
  while ((fgets(buf, MAX_STRLEN + 2, fp) != NULL) && length < MAX_ELEMENTS)
  {
    char *eoln = strchr(buf, '\n');
    if (eoln == NULL)
      buf[MAX_STRLEN] = '\0';
    else
      *eoln = '\0';
    *cur = (char *)malloc(strlen(buf) * sizeof(char) + 1);
    strcpy(*cur, buf);
    length++;
    cur++;
  }
  fclose(fp);

  // Given the flag, convert and sort the file
  if (i_flag == 1)
  {
    int *arr = (int *)malloc(length * sizeof(int));
    convert_to_ints(strings, arr, length);
    quicksort(arr, length, sizeof(int), int_cmp);
    print_array(arr, INT, length);
    free(arr);
  }
  else if (d_flag == 1)
  {
    double *arr = (double *)malloc(length * sizeof(double));
    convert_to_dbls(strings, arr, length);
    quicksort(arr, length, sizeof(double), dbl_cmp);
    print_array(arr, DOUBLE, length);
    free(arr);
  }
  else
  {
    quicksort(strings, length, sizeof(char *), str_cmp);
    print_array(strings, STRING, length);
  }

  // Cleanup (freeing heap)
  cur = strings;
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    free(*(cur++));
  }
  free(strings);
  free(buf);

  return EXIT_SUCCESS;
}
