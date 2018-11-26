//
// Created by Patrick on 2018-10-22.
//

#ifndef ZOMBIE_SURVIVAL_TEXTURE_H
#define ZOMBIE_SURVIVAL_TEXTURE_H

#include "Globals.h"

typedef enum MenuTextureNumber{
    tFONT_1,
    tBUTTON,tBUTTON_OVER,
    tBUTTON_RADIO_OFF,tBUTTON_RADIO_OVER,tBUTTON_RADIO_ON,
    tGRASS_TILE,tWOOD_TILE
}MenuTextureNumber;

typedef enum GameTextureNumber{
    tGRASS_TILE_1,tGRASS_TILE_2,tGRASS_TILE_3,tGRASS_TILE_4,
    tWOOD_TILE_1,tWOOD_TILE_2,tWOOD_TILE_3,tWOOD_TILE_4,
    tENTITY_DAMAGED,
    tSOLDIER_STAND,tSOLDIER_PISTOL,tSOLDIER_UZI,tSOLDIER_SNIPER,tSOLDIER_RPG,
    tZOMBIE_BASIC_STAND,tZOMBIE_NO_WEAPON,
    tBULLET_PISTOL,tBULLET_UZI,tBULLET_SNIPER,tBULLET_RPG,
    tLOOT_UZI,tLOOT_SNIPER,tLOOT_RPG
}GameTextureNumber;

// Menu
void load_menu_fonts();
void render_menu_text(SDL_Rect dest, MenuTextureNumber menu_texture_number, char *str, SDL_Color text_color);
void load_menu_textures();
SDL_Texture *get_menu_texture(MenuTextureNumber menuTextureNumber);
void destroy_menu_textures();

// Both
void load_player_font();
void render_player_text(Coordinate pos, char *str, SDL_Color text_color);

// Game
void load_game_textures();
SDL_Texture *get_game_texture(GameTextureNumber textureNumber);
void destroy_game_textures();

#endif //ZOMBIE_SURVIVAL_TEXTURE_H
