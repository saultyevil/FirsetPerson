/* ************************************************************************** */
/**
 * @file   terminal.c
 * @date   May 2020
 * @author E. J. Parkinson
 *
 * @brief Functions for setting up the terminal using NCurses.
 *
 * ************************************************************************** */

#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>

#include "firstPerson.h"

/* ************************************************************************** */
/**
 * @brief              
 *
 * @details
 *
 * ************************************************************************** */

void
terminalInit (void)
{  
  int screenSize;

  setlocale (LC_ALL, "");

  initscr (); 
  getmaxyx (stdscr, gameConfig.screenHeight, gameConfig.screenWidth);
  noecho ();
  cbreak ();
  keypad (stdscr, FALSE);  // Use NCurses defined FALSE, just in case ;-)
  curs_set (0);
  refresh ();

  // Allocate memory for the screen buffer
  screenSize        = gameConfig.screenHeight * gameConfig.screenWidth;
  gameConfig.screen = malloc (screenSize * sizeof *gameConfig.screen + 1);
  gameConfig.window = newwin (gameConfig.screenHeight, gameConfig.screenWidth, 0, 0);
  keypad (gameConfig.window, TRUE);
  nodelay (gameConfig.window, TRUE);
}

/* ************************************************************************** */
/**
 * @brief              
 *
 * @details
 *
 * ************************************************************************** */

void
terminalRevert (void)
{
  delwin (gameConfig.window);
  endwin ();
}  

/* ************************************************************************** */
/**
 * @brief  Update the terminal screen size and redraw.
 *
 * @param[in]  sig  an unused variable which is required for signal
 *
 * @details
 *
 * This is called by signal. When signal detects a SIGWINCH signal, then this
 * function is called and the terminal size is determined again. The screen is
 * then refreshed.
 *
 * ************************************************************************** */

void
terminalUpdateSize (int sig)
{
  (void) sig;

  terminalRevert ();
  terminalInit ();
  refreshScreen ();
}
