//
// Created by Patrick on 2018-10-22.
//

#ifndef ZOMBIE_SURVIVAL_GLOBALS_H
#define ZOMBIE_SURVIVAL_GLOBALS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

extern int const SCREEN_WIDTH;
extern int const SCREEN_HEIGHT;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
SDL_MouseButtonEvent mouse_event;

#define MAP_SIZE 14
int map[MAP_SIZE][MAP_SIZE];
extern int const TILE_SIZE;

extern int const ZOMBIE_PRECISION;

typedef enum MapType{GRASS,WOOD}MapType;
typedef enum UnitID{uPLAYER_ONE,uPLAYER_TWO,uZOMBIE_BASIC }UnitID;
extern int const number_of_weapons;
typedef enum WeaponNumber{NO_WEAPON,PISTOL,UZI,SNIPER,RPG}WeaponNumber;
typedef enum LootType{NO_LOOT,PISTOL_AMMO,UZI_AMMO,SNIPER_AMMO,RPG_AMMO}LootType;

typedef struct Coordinate{
    double x;
    double y;
}Coordinate;

bool player_two_active;
MapType map_type;

double distance(Coordinate pos1, Coordinate pos2);

#endif //ZOMBIE_SURVIVAL_GLOBALS_H
