/** **************************************************************************
 *
 * @file util.c
 * @date 01/01/2019
 * @author E. J. Parkinson
 *
 * @brief Utility functions for Kris.
 *
 * ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "SimpleFP.h"

/** **************************************************************************
 *
 *  @brief              Refresh the terminal screen
 *
 *  @return             void
 *
 *  @details
 *
 *  Resets the terminal display by clearing everything and repositioning the
 *  cursor or something. Can't quite remember what it's doing exactly.
 *
 * ************************************************************************** */

void
UtilResetDisplay (void)
{
  /*
   * \x1b is the escape character
   * \x1b[ is an escape sequence
   */

  write (STDOUT_FILENO, "\x1b[2J", 4);   // erase screen
  write (STDOUT_FILENO, "\x1b[H", 3);    // reposition the cursor
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
UtilExit (char *s)
{
  UtilResetDisplay ();
  perror (s);
  exit (errno);
}
