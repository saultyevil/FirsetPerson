/* ************************************************************************** */
/**
 *	@file     map.c
 *  @author   E. J. Parkinson
 *  @date     May 2020
 *
 * ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SimpleFP.h"

/* ************************************************************************** */
/** 
 * @brief Initialise the map
 *
 * @details
 * 
 * ************************************************************************** */

void
MapInit (void)
{
  struct GameMap Map = MAP_INIT;
  char  *TheMap = 
    "################"
    "#.........#....#"
    "######..###....#"
    "#...#.....##..##"
    "#..............#"
    "#..............#"
    "#...#..........#"
    "#...#..........#"
    "#...###..#######"
    "#...#..........#"
    "#..............#"
    "#...#..........#"
    "#...#######..###"
    "#...#..........#"
    "#....#.........#"
    "################";

  //First check that the hardcoded map is the correct size
  if ((int) strlen (TheMap) != FIXED_MAP_HEIGHT * FIXED_MAP_WIDTH)
  {
    printf ("MapInit : hardcoded map has incorrect number of cells %d when %d is expected (%ix%i)\n", 
            (int) strlen (TheMap), FIXED_MAP_WIDTH * FIXED_MAP_HEIGHT, FIXED_MAP_WIDTH, FIXED_MAP_HEIGHT);
    exit (EXIT_FAILURE);
  }

  // Initialise map variables and store in GameConfig
  Map.MapWidth       = FIXED_MAP_WIDTH;
  Map.MapHeight      = FIXED_MAP_HEIGHT;   
  Map.MapPoints      = Map.MapWidth * Map.MapHeight;
  Map.Map            = TheMap; 
  GameConfig.GameMap = Map;
}
