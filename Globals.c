//
// Created by Patrick on 2018-10-22.
//

#include "Globals.h"

int const SCREEN_WIDTH = 700;
int const SCREEN_HEIGHT = 700;
int const TILE_SIZE = 50;

int const ZOMBIE_PRECISION = 10; // the smaller the value the more precise

int const number_of_weapons = 5;

double distance(Coordinate pos1, Coordinate pos2)
{
    return sqrt(pow(pos1.x-pos2.x,2)+pow(pos1.y-pos2.y,2));
}