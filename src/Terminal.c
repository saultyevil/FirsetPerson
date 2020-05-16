/** **************************************************************************
 *
 * @file term.c
 * @date 01/01/2019
 * @author E. J. Parkinson
 *
 * @brief Functions for controlling terminal init and operations.
 *
 * ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "SimpleFP.h"

/** **************************************************************************
 *
 *  @brief              Set the original terminal flags at exit and clean memory
 *
 *  @return             void
 *
 *  @details
 *
 *  Cleans up the memory foot print of the text buffer and editor. The terminal
 *  is then revert to its original attributes.
 *
 * ************************************************************************** */

void
TerminalRevert (void)
{
  /*
   * Revert back the original term
   */

  if (tcsetattr (STDIN_FILENO, TCSAFLUSH, &GameConfig.original_terminal) == -1)
    UtilExit ("Can't set terminal attributes");
}

/** **************************************************************************
 *
 *  @brief              Enable raw terminal mode by changing terminal flags
 *
 *  @return             void
 *
 *  @details
 *
 *  Initialises the terminal so it is ready to ignore most input apart from what
 *  is desired. The original attributes of the terminal are also recorded and
 *  atexit is used so upon exit of the editor, the terminal is returned back
 *  to its original state.
 *
 * ************************************************************************** */

void
TerminalInit (void)
{
  struct termios raw_term;
  
  signal (SIGWINCH, TerminalUpdateSize);

  /*
   * Get the original attributes of the terminal before it is changed to raw
   * mode and assign to exit function to run at exit which will re-enable the
   * original terminal mode and clean up memory
   */

  if (tcgetattr (STDIN_FILENO, &GameConfig.original_terminal) == -1)
    UtilExit ("Can't get terminal attributes");
  atexit (TerminalRevert);

  /*
   * Enable raw terminal with some weird bit level operations,
   *    Control flags: Set 8 bit chars
   *    Output modes: disable post processing
   *    Local modes: echoing off, canonical off, no extended functions, no signal
   *    chars
   *    Input modes: no break, no CR to NL, no parity check, no strip char,
   *    no start/stop output control
   * Also enable the terminal to return each time a char is input with VMIN.
   */

  raw_term = GameConfig.original_terminal;
  raw_term.c_cflag |= (CS8);
  raw_term.c_oflag &= ~(OPOST);
  raw_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw_term.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw_term.c_cc[VMIN] = 0;
  raw_term.c_cc[VTIME] = 1;

  // Apply the attributes to the terminal
  GameConfig.current_terminal = raw_term;
  if (tcsetattr (STDIN_FILENO, TCSAFLUSH, &raw_term) == -1)
    UtilExit ("Can't set terminal attributes");

  TerminalGetWindowSize (&GameConfig.ScreenWidth, &GameConfig.ScreenHeight);
}

/** **************************************************************************
 *
 *  @brief              Get the current position of the cursor if the library
 *                      function is unable to.
 *
 *  @param[in, out]     *nrows      The number of terminal rows
 *  @param[in, out]     *ncols      The number of terminal columns
 *
 *  @return             void
 *
 *  @details
 *
 *  This is some witchcraft which moves the terminal cursor all over the place
 *  to figure out the number of rows and columns displayed in the current
 *  terminal.
 *
 * ************************************************************************** */

int
TerminalGetCursorPosition (int *nrows, int *ncols)
{
  unsigned i;
  char buf[32];

  if (write (STDOUT_FILENO, "\x1b[6n", 4) != 4)
    return -1;

  i = 0;
  while (i < sizeof (buf) - 1)
  {
    if (read (STDIN_FILENO, &buf[i], 1) != 1)
      break;
    if (buf[i] == 'R')
      break;
    i++;
  }

  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[')
    return -1;
  if (sscanf (&buf[2], "%d;%d", ncols, nrows) != 2)
    return -1;

  return 0;
}

/** **************************************************************************
 *
 *  @brief              Determine the size of the terminal window
 *
 *  @param[in, out]     *nrows      The number of terminal rows
 *  @param[in, out]     *ncols      The number of terminal columns
 *
 *  @return             FAILURE or SUCCESS
 *
 *  @details
 *
 *  The number of rows and columns on display in the terminal is returned from
 *  this function by either using ioctl, or by using the witchcraft function
 *  above if ioctl fails.
 *
 * ************************************************************************** */

int
TerminalGetWindowSize (int *ncols, int *nrows)
{
  struct winsize ws;

  /*
   * Query screen dimensions using ioctl
   */

  if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
  {
    /*
     * If ioctl fails, then do work around
     */

    if (write (STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
    {
      return EXIT_FAILURE;
    }

    return TerminalGetCursorPosition (nrows, ncols);
  }

  *ncols = ws.ws_col;
  *nrows = ws.ws_row;

  return EXIT_SUCCESS;
}

/** **************************************************************************
 *
 *  @brief              If a SIGWINCH is sent, update the terminal size
 *
 *  @param[in]          unused    an unused variable which is required for signal
 *
 *  @return             void
 *
 *  @details
 *
 *  This is called by signal. When signal detects a SIGWINCH signal, then this
 *  function is called and the terminal size is determined again. The screen is
 *  then refreshed.
 *
 * ************************************************************************** */

void
TerminalUpdateSize (int unused)
{
  char *NewScreen;

  (void) unused;

  TerminalGetWindowSize (&GameConfig.ScreenWidth, &GameConfig.ScreenHeight);
  NewScreen = realloc (GameConfig.Screen, GameConfig.ScreenWidth * GameConfig.ScreenHeight * sizeof *NewScreen + 1);
  
  if (!NewScreen)
    UtilExit ("TerminalUpdateSize: unable to allocate memory for new screen");

  GameConfig.Screen = NewScreen;
  RefreshScreen ();
}
