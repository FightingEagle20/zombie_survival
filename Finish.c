//
// Created by Patrick on 2018-10-22.
//

#include "Finish.h"
#include "Globals.h"

#include "Textures.h"

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}