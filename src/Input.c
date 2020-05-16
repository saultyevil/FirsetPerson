/* ************************************************************************** */
/**
 *	@file     Input.c
 *  @author   E. J. Parkinson
 *  @date     May 2020
 *
 * ************************************************************************** */

#include <math.h>
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
ControlPlayer (float TimeDifference)
{
  int     Key;
  float   PlayerX         = GameConfig.PlayerX;
  float   PlayerY         = GameConfig.PlayerY;
  float   PlayerDirection = GameConfig.PlayerDirection;
  float   PlayerSpeed     = GameConfig.PlayerSpeed;
  WINDOW *Window          = GameConfig.Window;
  
  struct  GameMap Map;
  Map.MapWidth = GameConfig.GameMap.MapWidth;
  Map.Map      = GameConfig.GameMap.Map;

  if ((Key = wgetch (Window)) != ERR)
  {
    switch (Key)
    {
      case KEY_RESIZE:
        TerminalUpdateSize (0);
        break;
      case KEY_DOWN:
        PlayerX -= sin (PlayerDirection) * PlayerSpeed * TimeDifference;
        PlayerY -= cos (PlayerDirection) * PlayerSpeed * TimeDifference;
        if (Map.Map[(int) PlayerY * Map.MapWidth + (int) PlayerX] == '#')
        {
          PlayerX += sin (PlayerDirection) * PlayerSpeed * TimeDifference;
          PlayerY += cos (PlayerDirection) * PlayerSpeed * TimeDifference;
        }
        break;
      case KEY_UP:
        PlayerX += sin (PlayerDirection) * PlayerSpeed * TimeDifference;
        PlayerY += cos (PlayerDirection) * PlayerSpeed * TimeDifference;
        if (Map.Map[(int) PlayerY * Map.MapWidth + (int) PlayerX] == '#')
        {
          PlayerX -= sin (PlayerDirection) * PlayerSpeed * TimeDifference;
          PlayerY -= cos (PlayerDirection) * PlayerSpeed * TimeDifference;
        }
        break;
      case KEY_LEFT:
        PlayerDirection -= (PlayerSpeed * 0.5) * TimeDifference;
        break;
      case KEY_RIGHT:
        PlayerDirection += (PlayerSpeed * 0.5) * TimeDifference;
        break;
      case 'q':
        TerminalRevert ();
        exit (EXIT_SUCCESS);
        break;
      default:
        break;
    }

    GameConfig.PlayerX         = PlayerX;
    GameConfig.PlayerY         = PlayerY;
    GameConfig.PlayerDirection = PlayerDirection;
  }
}
