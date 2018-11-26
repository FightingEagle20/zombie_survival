//
// Created by Patrick on 2018-11-14.
//

#include "Menu.h"

#include "Globals.h"
#include "Textures.h"
#include "MenuElements.h"
#include "Timer.h"

void setup_menu()
{
    set_in_main();
    load_player_font();
    load_menu_fonts();
    load_menu_textures();
    setup_elements();
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
}

void handle_inputs(bool *quit, bool *play)
{
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse_x, &mouse_y);
                handle_mouseover();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT) {
                   handle_clicks(play);
                }
                break;
            case SDL_QUIT:
                *quit = true;
                break;
            default:
                // nothing happens
                break;
        }
    }
}

void menu_loop(bool *quit)
{
    bool play =  false;
    while(!play) {
        calculate_timePassed();

        handle_inputs(quit, &play);
        if(*quit == true)
            break;

        SDL_RenderClear(renderer);

        render_menu();

        cap_frame_rate();
        SDL_RenderPresent(renderer);
        set_lastTick();
    }
}

void close_menu()
{
    destroy_menu_textures();
}