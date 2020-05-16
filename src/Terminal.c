/* ************************************************************************** */
/**
 * @file   Terminal.c
 * @date   01/01/2019
 * @author E. J. Parkinson
 *
 * @brief Functions for setting up the terminal using NCurses.
 *
 * ************************************************************************** */

#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>

#include "SimpleFP.h"

/* ************************************************************************** */
/**
 * @brief              
 *
 * @details
 *
 * ************************************************************************** */

void
TerminalInit (void)
{  
  int ScreenSize;

  setlocale (LC_ALL, "");

  initscr (); 
  getmaxyx (stdscr, GameConfig.ScreenHeight, GameConfig.ScreenWidth);
  noecho ();
  cbreak ();
  keypad (stdscr, FALSE);  // Use NCurses defined FALSE, just in case ;-)
  curs_set (0);
  refresh ();

  // Allocate memory for the screen buffer
  ScreenSize        = GameConfig.ScreenHeight * GameConfig.ScreenWidth;
  GameConfig.Screen = malloc (ScreenSize * sizeof *GameConfig.Screen + 1);
  GameConfig.Window = newwin (GameConfig.ScreenHeight, GameConfig.ScreenWidth, 0, 0);
  keypad (GameConfig.Window, TRUE);
  nodelay (GameConfig.Window, TRUE);
}

/* ************************************************************************** */
/**
 * @brief              
 *
 * @details
 *
 * ************************************************************************** */

void
TerminalRevert (void)
{
  delwin (GameConfig.Window);
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
TerminalUpdateSize (int sig)
{
  (void) sig;

  TerminalRevert ();
  TerminalInit ();
  RefreshScreen ();
}
