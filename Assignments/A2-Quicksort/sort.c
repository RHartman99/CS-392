/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : September 11th, 2019
 * Description : Finds all prime numbers from 2 to n as long as n is greater than 2.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "quicksort.h"

enum DATA_TYPE
{
  INT,
  DOUBLE,
  STRING
};

void print_usage()
{
  printf("Usage: ./sort [-i|-d] [filename]\n");
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
      print_usage();
      return EXIT_FAILURE;
    }
  }
  if (i_flag + d_flag > 1)
  {
    printf("Error: Too many options enabled.\n");
    print_usage();
    return EXIT_FAILURE;
  }
  else if (i_flag == 1)
  {
    puts("Integers");
  }
  else if (d_flag == 1)
  {
    puts("Doubles");
  }
  else
  {
    puts("Strings");
  }
  return EXIT_SUCCESS;
}

// Strerror? Do you mean stderror?
// Should you print to stderror when an invalid flag?
// Do we error if too many options are enabled? Do we return EXIT_FAILURE?
// What if they enter two filenames?