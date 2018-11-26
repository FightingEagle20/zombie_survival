//
// Created by Patrick on 2018-11-14.
//

#include "Game.h"

#include <string.h>

#include "Textures.h"
#include "Player.h"
#include "Zombie.h"
#include "Timer.h"
#include "Map.h"
#include "Loot.h"

Entity player1,player2;
Zombie zombies;

void setup_players()
{
    player_setup(&player1, tSOLDIER_STAND, uPLAYER_ONE);
    player_setup(&player2, tSOLDIER_STAND, uPLAYER_TWO);
}

void setup_zombies()
{
    zombies.zombie = NULL;
    zombies.zombie_count = 0;
}

void setup_game()
{
    load_player_font();
    load_game_textures();
    load_map();
    setup_players();
    setup_zombies();
}

void handle_game_inputs(bool *quit)
{
    while(SDL_PollEvent(&event)) {
        player_handle_input(&player1);
        if(player_two_active)
            player_handle_input(&player2);
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                *quit = true;
            }
        }
        if(event.type == SDL_QUIT) {
            *quit = true;
        }
    }
}

void shoot()
{
    shoot_player(&player1);
    if(player_two_active)
        shoot_player(&player2);
}

void move(bool *quit)
{
    move_player(&player1);
    if(player_two_active)
        move_player(&player2);
    move_player_projectiles(&zombies);
    move_zombies(zombies, &player1, &player2, quit);
}

void render_game()
{
    render_map();
    render_all_loot();
    render_player(&player1);
    if(player_two_active)
        render_player(&player2);
    render_player_projectiles();
    render_zombies(&zombies);
}

void decrease_spawn_interval(uint32_t *interval)
{
    uint32_t t = get_timeSinceStart();
    // starts at 2000 goes to 1000 after 50 seconds, 500 after 100 seconds
    *interval = (uint32_t)round((double)1/10000000*pow(t,2)-(double)1/40*t+2000);
}

void game_loop()
{
    uint32_t zombie_spawn_interval = 2000;
    bool quit = false;
    start_Timer();
    while( !quit ) {
        calculate_timePassed();

        handle_game_inputs(&quit);
        decrease_spawn_interval(&zombie_spawn_interval);

        SDL_RenderClear(renderer);

        spawn_zombie_logic(&zombies,zombie_spawn_interval);
        shoot();
        move(&quit);
        render_game();

        cap_frame_rate();
        SDL_RenderPresent(renderer);

        set_lastTick();
    }
    end_Timer();
}

bool in_eng_abc(char c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    return false;
}

void push(char *str, char c)
{
    int len = strlen(str);
    str[len] = c;
    str[len+1] = '\0';
}

void pop(char *str)
{
    int len = strlen(str);
    str[len-1] = '\0';
}

void handle_end_inputs(bool *done, char *player_name, int *length)
{
    char next_char;

    SDL_StartTextInput();
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                *done = true;
                break;
            case SDL_TEXTINPUT:
                if(*length <= 12) {
                    next_char = event.text.text[0];
                    if(in_eng_abc(next_char)) {
                        push(player_name, next_char);
                        (*length)++;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_RETURN) {
                    *done = true;
                } else if(event.key.keysym.sym == SDLK_BACKSPACE) {
                    if(*length > 0) {
                        pop(player_name);
                        (*length)--;
                    }
                }
            default:
                // nothing happens
                break;
        }
    }
}

void render_rect_filled(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void render_rect_outline(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void render_end(char *player_name)
{
    // Colors
    SDL_Color black = {0,0,0,128};
    SDL_Color white = {255,255,255,128};
    SDL_Color faded_black = {0,0,0,128};

    // Background
    SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    render_rect_filled(background, faded_black);

    // Inout box
    int width = SCREEN_WIDTH*10/24;
    int height= SCREEN_HEIGHT/20;
    SDL_Rect box = {SCREEN_WIDTH/2-width/2, SCREEN_HEIGHT/2-height/2 ,width, height};

    render_rect_filled(box, black);
    render_rect_outline(box, white);

    // Title
    render_player_text((Coordinate){SCREEN_WIDTH/2, SCREEN_HEIGHT/4}, "GAME ENDED", white);

    // Score
    char score_str[11+12+1] = "Your score: ";
    char score[12];
    sprintf(score, "%d", get_gameTickCount()/1000);
    strcat(score_str,score);
    render_player_text((Coordinate){SCREEN_WIDTH/2, SCREEN_HEIGHT/3}, score_str, white);

    // Input
    if(strlen(player_name) > 0)
        render_player_text((Coordinate){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, player_name, white);
}

void save_player_score(char *player_name)
{
    if(strlen(player_name) == 0)
        player_name = ".";

    FILE *f = fopen("scores/high_scores.txt","r");
    char tmp_name[12+1];
    int tmp_score;
    char player_names[5][12+1] = {".",".",".",".","."};
    int scores[5] = {0};
    int i = 0;
    while(fscanf(f, "%s %d", tmp_name, &tmp_score) != EOF) {
        strcpy(player_names[i], tmp_name);
        scores[i] = tmp_score;
        i++;
    }
    bool written = false;
    int player_score = get_gameTickCount()/1000;
    freopen("scores/high_scores.txt", "w", f);
    i = 0;
    for(int j=0;j<5;j++) {
        if(!written && scores[i] <= player_score) {
            fprintf(f, "%s %d\n", player_name, player_score);
            written = true;
        } else {
            fprintf(f, "%s %d\n", player_names[i], scores[i]);
            i++;
        }
    }
    fclose(f);
}

void end_screen()
{
    char player_name[12+1] = "NAME";
    int length = 4;
    bool done = false;
    while( !done ) {
        calculate_timePassed();
        handle_end_inputs(&done, player_name, &length);

        SDL_RenderClear(renderer);

        render_game();
        render_end(player_name);

        cap_frame_rate();
        SDL_RenderPresent(renderer);
        set_lastTick();
    }
    save_player_score(player_name);
}

void close_game()
{
    free_all_loot();
    free_projectiles();
    free_zombies(&zombies);
    destroy_game_textures();
}