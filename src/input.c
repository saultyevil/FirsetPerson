/* ************************************************************************** */
/**
 *	@file     input.c
 *  @date     May 2020
 *  @author   E. J. Parkinson
 *
 * ************************************************************************** */

#include <math.h>
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
controlPlayer (float timeDifference)
{
  int     key;
  float   playerX         = gameConfig.playerX;
  float   playerY         = gameConfig.playerY;
  float   playerDirection = gameConfig.playerDirection;
  float   playerSpeed     = gameConfig.playerSpeed;
  WINDOW *window          = gameConfig.window;
  
  struct  gameMap map;
  map.mapWidth = gameConfig.gameMap.mapWidth;
  map.map      = gameConfig.gameMap.map;

  if ((key = wgetch (window)) != ERR)
  {
    switch (key)
    {
      case KEY_RESIZE:
        terminalUpdateSize (0);
        break;
      case KEY_DOWN:
        playerX -= sin (playerDirection) * playerSpeed * timeDifference;
        playerY -= cos (playerDirection) * playerSpeed * timeDifference;
        if (map.map[(int) playerY * map.mapWidth + (int) playerX] == '#')
        {
          playerX += sin (playerDirection) * playerSpeed * timeDifference;
          playerY += cos (playerDirection) * playerSpeed * timeDifference;
        }
        break;
      case KEY_UP:
        playerX += sin (playerDirection) * playerSpeed * timeDifference;
        playerY += cos (playerDirection) * playerSpeed * timeDifference;
        if (map.map[(int) playerY * map.mapWidth + (int) playerX] == '#')
        {
          playerX -= sin (playerDirection) * playerSpeed * timeDifference;
          playerY -= cos (playerDirection) * playerSpeed * timeDifference;
        }
        break;
      case KEY_LEFT:
        playerDirection -= (playerSpeed * 0.5) * timeDifference;
        break;
      case KEY_RIGHT:
        playerDirection += (playerSpeed * 0.5) * timeDifference;
        break;
      case 'q':
        terminalRevert ();
        exit (EXIT_SUCCESS);
      default:
        break;
    }

    gameConfig.playerX         = playerX;
    gameConfig.playerY         = playerY;
    gameConfig.playerDirection = playerDirection;
  }
}
