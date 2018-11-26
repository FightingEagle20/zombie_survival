//
// Created by Patrick on 2018-10-22.
//

#include "Textures.h"

SDL_Texture *loadTexture(char *path)
{
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

//
// Menu
//

#define NUMBER_OF_MENU_FONTS 1
#define NUMBER_OF_MENU_TEXTURES 8

TTF_Font *menuFonts[NUMBER_OF_MENU_FONTS];
SDL_Texture *menuTextures[NUMBER_OF_MENU_TEXTURES];

void load_menu_fonts()
{
    menuFonts[tFONT_1] = TTF_OpenFont("fonts/kenney_future_narrow.ttf", 24);
    if(menuFonts[tFONT_1] == NULL) {
        printf("Failed to load lazy tFONT1! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

void render_menu_text(SDL_Rect dest, MenuTextureNumber menu_texture_number, char *str, SDL_Color text_color)
{
    SDL_DestroyTexture(menuTextures[menu_texture_number]);
    SDL_Surface *text_surface = TTF_RenderText_Solid(menuFonts[menu_texture_number], str, text_color);
    if(text_surface != NULL) {
        menuTextures[menu_texture_number] = SDL_CreateTextureFromSurface(renderer, text_surface);
        if(menuTextures[menu_texture_number] == NULL) {
            printf("Unable to create texture from text_surface! SDL Error: %s\n", SDL_GetError());
        } else {
//            width = text_surface->w;
//            height = text_surface->h;

            dest.w = dest.w/2;
            dest.h = dest.h/2;
            dest.x = dest.x - dest.w/2;
            dest.y = dest.y - dest.h/2;

            SDL_RenderCopy(renderer, menuTextures[menu_texture_number], NULL, &dest);
        }

        SDL_FreeSurface(text_surface);
    } else {
        printf("Unable to render text to surface in render_player_text! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

void load_menu_textures()
{
    menuTextures[tBUTTON] = loadTexture("textures/button.png");
    menuTextures[tBUTTON_OVER] = loadTexture("textures/button_over.png");
    menuTextures[tBUTTON_RADIO_OFF] = loadTexture("textures/button_radio_off.png");
    menuTextures[tBUTTON_RADIO_OVER] = loadTexture("textures/button_radio_over.png");
    menuTextures[tBUTTON_RADIO_ON] = loadTexture("textures/button_radio_on.png");
    menuTextures[tGRASS_TILE] = loadTexture("textures/grass_01.png");
    menuTextures[tWOOD_TILE] = loadTexture("textures/wood_03.png");
}

SDL_Texture *get_menu_texture(MenuTextureNumber menuTextureNumber)
{
    if(menuTextureNumber >= NUMBER_OF_MENU_TEXTURES) {
        printf("Error: Tried to get the texture of '%d'!\n", menuTextureNumber);
        return NULL;
    }
    return menuTextures[menuTextureNumber];
}

void destroy_menu_textures()
{
    for(int i=0;i<NUMBER_OF_MENU_FONTS;i++) {
        TTF_CloseFont(menuFonts[i]);
        menuFonts[i] = NULL;
    }
    for(int i=0;i<NUMBER_OF_MENU_TEXTURES;i++) {
        SDL_DestroyTexture(menuTextures[i]);
        menuTextures[i] = NULL;
    }
}

//
// BOTH
//

TTF_Font *fontPlayerName;
SDL_Texture *playerFontTexture;

void load_player_font()
{
    fontPlayerName = TTF_OpenFont("fonts/kenney_future_narrow.ttf", 24);
    if(fontPlayerName == NULL) {
        printf("Failed to load lazy fontPlayerName! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

void render_player_text(Coordinate pos, char *str, SDL_Color text_color)
{
    SDL_DestroyTexture(playerFontTexture);
    SDL_Surface *text_surface = TTF_RenderText_Solid(fontPlayerName, str, text_color);
    if(text_surface != NULL) {
        playerFontTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if(playerFontTexture == NULL) {
            printf("Unable to create texture from text_surface! SDL Error: %s\n", SDL_GetError());
        } else {
            int width = text_surface->w;
            int height = text_surface->h;

            SDL_Rect dest = {(int)(pos.x-width/2), (int)(pos.y-height/2), width, height};
            SDL_RenderCopy(renderer, playerFontTexture, NULL, &dest);
        }


        SDL_FreeSurface(text_surface);
    } else {
        printf("Unable to render text to surface in render_player_text! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

//
// GAME
//

#define NUMBER_OF_GAME_TEXTURES 23

SDL_Texture *gameTextures[NUMBER_OF_GAME_TEXTURES];

void load_game_textures()
{
    gameTextures[tGRASS_TILE_1]       = loadTexture("textures/grass_01.png");
    gameTextures[tGRASS_TILE_2]       = loadTexture("textures/grass_02.png");
    gameTextures[tGRASS_TILE_3]       = loadTexture("textures/grass_03.png");
    gameTextures[tGRASS_TILE_4]       = loadTexture("textures/grass_04.png");
    gameTextures[tWOOD_TILE_1]       = loadTexture("textures/wood_01.png");
    gameTextures[tWOOD_TILE_2]       = loadTexture("textures/wood_02.png");
    gameTextures[tWOOD_TILE_3]       = loadTexture("textures/wood_03.png");
    gameTextures[tWOOD_TILE_4]       = loadTexture("textures/wood_04.png");
    gameTextures[tENTITY_DAMAGED]     = loadTexture("textures/entity_damaged.png");
    gameTextures[tSOLDIER_STAND]      = loadTexture("textures/soldier1_stand.png");
    gameTextures[tSOLDIER_PISTOL]     = loadTexture("textures/soldier_pistol.png");
    gameTextures[tSOLDIER_UZI]        = loadTexture("textures/soldier_uzi.png");
    gameTextures[tSOLDIER_SNIPER]     = loadTexture("textures/soldier_sniper.png");
    gameTextures[tSOLDIER_RPG]        = loadTexture("textures/soldier_rpg.png");
    gameTextures[tZOMBIE_BASIC_STAND] = loadTexture("textures/zombie_stand.png");
    gameTextures[tZOMBIE_NO_WEAPON]   = loadTexture("textures/zombie_no_weapon.png");
    gameTextures[tBULLET_PISTOL]      = loadTexture("textures/bullet_01.png");
    gameTextures[tBULLET_UZI]         = loadTexture("textures/bullet_02.png");
    gameTextures[tBULLET_SNIPER]      = loadTexture("textures/bullet_03.png");
    gameTextures[tBULLET_RPG]         = loadTexture("textures/bullet_04.png");
    gameTextures[tLOOT_UZI]           = loadTexture("textures/loot_uzi.png");
    gameTextures[tLOOT_SNIPER]        = loadTexture("textures/loot_sniper.png");
    gameTextures[tLOOT_RPG]           = loadTexture("textures/loot_rpg.png");
}

SDL_Texture *get_game_texture(GameTextureNumber textureNumber)
{
    if(textureNumber == -1) {
        printf("Error: Tried to get the texture of '-1' = 'NO_WEAPON'!\n");
    } else if(textureNumber == -2) {
        printf("Error: Tried to get the texture of '-2'!\n");
    } else if(textureNumber >= NUMBER_OF_GAME_TEXTURES) {
        printf("Error: Tried to get the texture of '%d'!\n",textureNumber);
    } else {
        return gameTextures[textureNumber];
    }
    return NULL;
}

void destroy_game_textures()
{
    TTF_CloseFont(fontPlayerName);
    fontPlayerName = NULL;
    SDL_DestroyTexture(playerFontTexture);
    playerFontTexture = NULL;

    for(int i=0;i<NUMBER_OF_GAME_TEXTURES;i++) {
        SDL_DestroyTexture(gameTextures[i]);
        gameTextures[i] = NULL;
    }
}
