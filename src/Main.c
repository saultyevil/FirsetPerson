/* ************************************************************************** */
/**
 *	@file     main.c
 *  @author   E. J. Parkinson
 *  @date     May 2020
 *
 * ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

#include "SimpleFP.h"

/* ************************************************************************** */
/** 
 * @brief
 *
 * @details
 * 
 * ************************************************************************** */

void
GameInit (void)
{
  atexit (TerminalRevert);
  // signal (SIGWINCH, TerminalUpdateSize);

  GameConfig.PlayerFOV       = M_PI / 4.0;
  GameConfig.PlayerX         = 1.5;
  GameConfig.PlayerY         = 1.5;
  GameConfig.PlayerDirection = 0.0;
  GameConfig.PlayerSpeed     = 100.0;
  GameConfig.RenderDepth     = 16.0;
  GameConfig.RayStepSize     = 0.1;
  GameConfig.Screen          = NULL;
}

/* ************************************************************************** */
/** 
 * @brief
 *
 * @details
 * 
 * ************************************************************************** */

int 
main (void)
{
  float  TimeDifference;
  struct timeval StartTime;
  struct timeval EndTime;

  GameInit ();
  TerminalInit ();
  MapInit ();

  gettimeofday (&StartTime, NULL);

  while (true)
  {
    gettimeofday (&EndTime, NULL);
    TimeDifference = (EndTime.tv_usec - StartTime.tv_usec) * 1e-6;
    RefreshScreen ();
    ControlPlayer (TimeDifference);
    StartTime = EndTime;
  }

  return 0;
}
