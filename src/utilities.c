/** **************************************************************************
 *
 * @file utilities.c
 * @date May 2020
 * @author E. J. Parkinson
 *
 * @brief Utility functions for Kris.
 *
 * ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "firstPerson.h"

/* ************************************************************************** */
/** 
 * @brief
 *
 * @details
 *
 * This is an implementation of Bubble sort. Since N_BOUNDARY_TESTS = 4, 
 * performance should not be a major problem (I think).
 * 
 * ************************************************************************** */

void
sortBoundaryTest (struct bTest *boundaryTest)
{
  int     i, j;
  struct  bTest temp;

  for (i = 0; i < N_BOUNDARY_TESTS - 1; ++i)
  {
    for (j = 0; j < N_BOUNDARY_TESTS - i - 1; ++j)
    {
      if (boundaryTest[j].distance > boundaryTest[j + 1].distance)
      {
        temp = boundaryTest[j];
        boundaryTest[j] = boundaryTest[j + 1];
        boundaryTest[j + 1] = temp;
      }
    }
  }
}

/** **************************************************************************
 *
 *  @brief              Kill the program and print an error message and string s
 *
 *  @param[in]          *s    An error message to print
 *
 *  @return             void
 *
 *  @details
 *
 *  Reset the terminal display, use perror to print the errno error with a
 *  message and then exit with errno error code.
 *
 * ************************************************************************** */

void
utilExit (char *s)
{
  terminalRevert ();
  perror (s);
  exit (errno);
}
