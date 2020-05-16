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
#include <locale.h>
#include <stdlib.h>

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

  setlocale (LC_ALL, "");

  // Initialise the player
  GameConfig.PlayerFOV       = M_PI / 4.0;
  GameConfig.PlayerX         = 8.0;
  GameConfig.PlayerY         = 6.0;
  GameConfig.PlayerDirection = 0.0;
  GameConfig.PlayerSpeed     = 5.0;

  // Set various variables for rendering
  GameConfig.RenderDepth     = 16.0;
  GameConfig.RayStepSize     = 0.1;

  // Allocate memory for the screen
  GameConfig.Screen          = malloc (GameConfig.ScreenWidth * GameConfig.ScreenHeight * sizeof *GameConfig.Screen + 1);
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
  int    Key;
  float  TimeDifference = 0.0;
  float  MaxFramePeriod = 1.0 / MAX_FPS * 1e6;
  struct timeval StartTime;
  struct timeval EndTime;

  TerminalInit ();
  GameInit ();
  MapInit ();

  gettimeofday (&StartTime, NULL);

  RefreshScreen ();
  return 0;

  while (true)
  {
    gettimeofday (&EndTime, NULL);
    TimeDifference = 1e6 * (EndTime.tv_sec - StartTime.tv_sec) + (EndTime.tv_usec - StartTime.tv_usec);

    if (TimeDifference >= MaxFramePeriod)
    {
      ControlPlayer (ReadKeypress (), TimeDifference / 1e6);
      RefreshScreen ();
      StartTime = EndTime;
    }
  }

  return 0;
}
