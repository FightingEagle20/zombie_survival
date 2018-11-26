//
// Created by Patrick on 2018-10-22.
//

#include "Start.h"

#include "Textures.h"

void init() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        printf("SDL initialisation failed: %s", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Zombie Survival", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(window == NULL) {
        printf("Window creation failed: %s", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Renderer creation failed: %s", SDL_GetError());
        exit(1);
    }

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    if(TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }
}