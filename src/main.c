/* ************************************************************************** */
/**
 *	@file     main.c
 *  @date     May 2020
 *  @author   E. J. Parkinson
 *
 * ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

#include "firstPerson.h"

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
  gameConfig.playerFOV       = M_PI / 4.0;
  gameConfig.playerX         = 1.5;
  gameConfig.playerY         = 1.5;
  gameConfig.playerDirection = 0.0;
  gameConfig.playerSpeed     = 100.0;
  gameConfig.renderDepth     = 16.0;
  gameConfig.rayStepSize     = 0.1;
  gameConfig.screen          = NULL;
  atexit (terminalRevert);
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
  float  timeDifference;
  struct timeval startTime;
  struct timeval endTime;

  GameInit ();
  terminalInit ();
  mapInit ();

  gettimeofday (&startTime, NULL);

  while (true)
  {
    gettimeofday (&endTime, NULL);
    timeDifference = (endTime.tv_usec - startTime.tv_usec) * 1e-6;
    refreshScreen ();
    controlPlayer (timeDifference);
    startTime = endTime;
  }

  return 0;
}
