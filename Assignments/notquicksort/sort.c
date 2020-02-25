/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : September 11th, 2019
 * Description : Finds all prime numbers from 2 to n as long as n is greater than 2.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "quicksort.h"

#define BUFSIZE 128
#define MAX_EL 1024
#define MAX_CH 64

void print_usage(char *cmd)
{
  printf("Usage: %s [-i|-d] [filename]\n", cmd);
  printf("    -i: Specifies the file contains ints.\n");
  printf("    -d: Specifies the file contains doubles.\n");
  printf("    filename: The file to sort.\n");
  printf("    No flags defaults to sorting strings.\n");
}

void print_array(int arr[], int size)
{
  printf("[%d", arr[0]);
  for (int i = 1; i < size; i++)
  {
    printf(", %d", arr[i]);
  }
  printf("]");
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

  char words[MAX_EL][MAX_CH + 1];
  int line_count;
  int i = 0;
  while (fgets(words[i], MAX_CH, fp) != NULL)
  {
    words[i][strlen(words[i])] = '\0';
    printf("%s", words[i]);
    line_count++;
  }

  if (i_flag == 1)
  {
  }
  else if (d_flag == 1)
  {
  }
  else
  {
  }

  printf("\n\n%d", get_integer("24\n"));
  printf("\n\n%lf", get_double("24.214\n"));

  return EXIT_SUCCESS;
}

// Should you print to stderror when an invalid flag?
// Do we error if too many options are enabled? Do we return EXIT_FAILURE?
// What if they enter two filenames?