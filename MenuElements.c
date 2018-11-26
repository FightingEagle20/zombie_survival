//
// Created by Patrick on 2018-11-25.
//

#include "MenuElements.h"

bool in_main, in_start, in_board;

// Main
Element t_main_title;                           // Texts
Element b_start, b_board;                       // Buttons

// Start
Element t_number_of_players, t_which_map;       // Texts
Element t_singleplayer, t_cooperative;          // Texts
Element i_map_one, i_map_two;                   // Images
Element r_one_player, r_two_player;             // Radio buttons
Element r_map_one, r_map_two;                   // Radio buttons
Element b_play;                                 // Button

// Board
Element t_board_title, t_name[5], t_score[5];   // Texts
Element b_back;                                 // Buttons

void set_in_main()
{
    in_main = true;
}

void setup_main()
{
    t_main_title.pos.x = SCREEN_WIDTH/2;
    t_main_title.pos.y = SCREEN_HEIGHT/5;
    t_main_title.width = SCREEN_WIDTH*3/2;
    t_main_title.height = SCREEN_HEIGHT/5;
    strcpy(t_main_title.text, "Zombie Survival");
    t_main_title.active = false;
    t_main_title.type = TEXT;
    t_main_title.textureNumber = tFONT_1;

    b_start.pos.x = SCREEN_WIDTH/2;
    b_start.pos.y = SCREEN_HEIGHT*6/10;
    b_start.width = SCREEN_WIDTH*2/3;
    b_start.height = SCREEN_HEIGHT/10;
    strcpy(b_start.text, "START");
    b_start.active = false;
    b_start.type = BUTTON;
    b_start.textureNumber = tBUTTON;

    b_board.pos.x = SCREEN_WIDTH/2;
    b_board.pos.y = SCREEN_HEIGHT*16/20;
    b_board.width = SCREEN_WIDTH*2/3;
    b_board.height = SCREEN_HEIGHT/10;
    strcpy(b_board.text, "BOARD");
    b_board.active = false;
    b_board.type = BUTTON;
    b_board.textureNumber = tBUTTON;
}

void setup_start_texts()
{
    t_number_of_players.pos.x = SCREEN_WIDTH/2;
    t_number_of_players.pos.y = SCREEN_HEIGHT/10;
    t_number_of_players.width = SCREEN_WIDTH*3/2;
    t_number_of_players.height = SCREEN_HEIGHT/6;
    strcpy(t_number_of_players.text, "Choose number of players");
    t_number_of_players.active = false;
    t_number_of_players.type = TEXT;
    t_number_of_players.textureNumber = tFONT_1;

    t_singleplayer.pos.x = SCREEN_WIDTH*1/3;
    t_singleplayer.pos.y = SCREEN_HEIGHT/5;
    t_singleplayer.width = SCREEN_WIDTH*5/12;
    t_singleplayer.height = SCREEN_HEIGHT/12;
    strcpy(t_singleplayer.text, "Singleplayer");
    t_singleplayer.active = false;
    t_singleplayer.type = TEXT;
    t_singleplayer.textureNumber = tFONT_1;

    t_cooperative.pos.x = SCREEN_WIDTH*2/3;
    t_cooperative.pos.y = SCREEN_HEIGHT/5;
    t_cooperative.width = SCREEN_WIDTH*5/12;
    t_cooperative.height = SCREEN_HEIGHT/12;
    strcpy(t_cooperative.text, "Cooperative");
    t_cooperative.active = false;
    t_cooperative.type = TEXT;
    t_cooperative.textureNumber = tFONT_1;

    t_which_map.pos.x = SCREEN_WIDTH/2;
    t_which_map.pos.y = SCREEN_HEIGHT*7/20;
    t_which_map.width = SCREEN_WIDTH*2/3;
    t_which_map.height = SCREEN_HEIGHT/6;
    strcpy(t_which_map.text, "Choose map");
    t_which_map.active = false;
    t_which_map.type = TEXT;
    t_which_map.textureNumber = tFONT_1;
}

void setup_start_images()
{
    i_map_one.pos.x = SCREEN_WIDTH/4;
    i_map_one.pos.y = SCREEN_HEIGHT*6/10;
    i_map_one.width = SCREEN_WIDTH/3;
    i_map_one.height = SCREEN_HEIGHT/3;
    strcpy(i_map_one.text, "");
    i_map_one.active = false;
    i_map_one.type = IMAGE;
    i_map_one.textureNumber = tGRASS_TILE;

    i_map_two.pos.x = SCREEN_WIDTH*3/4;
    i_map_two.pos.y = SCREEN_HEIGHT*6/10;
    i_map_two.width = SCREEN_WIDTH/3;
    i_map_two.height = SCREEN_HEIGHT/3;
    strcpy(i_map_two.text, "");
    i_map_two.active = false;
    i_map_two.type = IMAGE;
    i_map_two.textureNumber = tWOOD_TILE;
}

void setup_start_buttons()
{
    r_one_player.pos.x = SCREEN_WIDTH*1/3;
    r_one_player.pos.y = SCREEN_HEIGHT*4/16;
    r_one_player.width = SCREEN_WIDTH/48;
    r_one_player.height = SCREEN_HEIGHT/48;
    strcpy(r_one_player.text, "");
    r_one_player.active = true;
    r_one_player.type = BUTTON;
    r_one_player.textureNumber = tBUTTON_RADIO_OFF;

    r_two_player.pos.x = SCREEN_WIDTH*2/3;
    r_two_player.pos.y = SCREEN_HEIGHT*4/16;
    r_two_player.width = SCREEN_WIDTH/48;
    r_two_player.height = SCREEN_HEIGHT/48;
    strcpy(r_two_player.text, "");
    r_two_player.active = false;
    r_two_player.type = BUTTON;
    r_two_player.textureNumber = tBUTTON_RADIO_OFF;

    r_map_one.pos.x = SCREEN_WIDTH/4;
    r_map_one.pos.y = SCREEN_HEIGHT*33/40;
    r_map_one.width = SCREEN_WIDTH/48;
    r_map_one.height = SCREEN_HEIGHT/48;
    strcpy(r_map_one.text, "");
    r_map_one.active = true;
    r_map_one.type = IMAGE;
    r_map_one.textureNumber = tBUTTON_RADIO_OFF;

    r_map_two.pos.x = SCREEN_WIDTH*3/4;
    r_map_two.pos.y = SCREEN_HEIGHT*33/40;
    r_map_two.width = SCREEN_WIDTH/48;
    r_map_two.height = SCREEN_HEIGHT/48;
    strcpy(r_map_two.text, "");
    r_map_two.active = false;
    r_map_two.type = IMAGE;
    r_map_two.textureNumber = tBUTTON_RADIO_OFF;

    b_play.pos.x = SCREEN_WIDTH/2;
    b_play.pos.y = SCREEN_HEIGHT*45/48;
    b_play.width = SCREEN_WIDTH*3/12;
    b_play.height = SCREEN_HEIGHT*1/12;
    strcpy(b_play.text, "Play");
    b_play.active = false;
    b_play.type = BUTTON;
    b_play.textureNumber = tBUTTON;
}

void setup_start()
{
    setup_start_texts();
    setup_start_images();
    setup_start_buttons();
}

void load_scores()
{
    FILE *f = fopen("scores/high_scores.txt", "r");
    int tmp_i = -1;
    char tmp_str[12+1];
    for(int i=0;i<5;i++) {
        fscanf(f, "%s %d", tmp_str, &tmp_i);
        strcpy(t_name[i].text,tmp_str);
        sprintf(t_score[i].text, "%d", tmp_i);
    }
    fclose(f);
}

void setup_scores()
{
    load_scores();
    double start_y = SCREEN_HEIGHT*5/12;
    for(int i=0;i<5;i++) {
        t_name[i].pos.x = SCREEN_WIDTH*1/3;
        t_name[i].pos.y = start_y + i * SCREEN_HEIGHT*1/12;
        t_name[i].type = TEXT;
        t_name[i].textureNumber = tFONT_1;

        t_score[i].pos.x = SCREEN_WIDTH*3/4;
        t_score[i].pos.y = start_y + i * SCREEN_HEIGHT*1/12;
        t_score[i].type = TEXT;
        t_score[i].textureNumber = tFONT_1;
    }
}

void setup_board()
{
    t_board_title.pos.x = SCREEN_WIDTH/2;
    t_board_title.pos.y = SCREEN_HEIGHT/5;
    t_board_title.width = SCREEN_WIDTH;
    t_board_title.height = SCREEN_HEIGHT/6;
    strcpy(t_board_title.text, "Leaderboard");
    t_board_title.active = false;
    t_board_title.type = TEXT;
    t_board_title.textureNumber = tFONT_1;

    setup_scores();

    b_back.pos.x = SCREEN_WIDTH*1.5/12;
    b_back.pos.y = SCREEN_HEIGHT*11/12;
    b_back.width = SCREEN_WIDTH*2/12;
    b_back.height = SCREEN_HEIGHT*1/12;
    strcpy(b_back.text, "Back");
    b_back.active = false;
    b_back.type = BUTTON;
    b_back.textureNumber = tBUTTON;
}

void setup_elements()
{
    setup_main();
    setup_start();
    setup_board();
}

void render_button(Element element, SDL_Rect dest)
{
    dest.x -= dest.w/2;
    dest.y -= dest.h/2;
    SDL_RenderCopy(renderer, get_menu_texture(element.textureNumber), NULL, &dest);
}

void round_values(Element *element)
{
    element->pos.x  = round(element->pos.x);
    element->pos.y  = round(element->pos.y);
    element->width  = round(element->width);
    element->height = round(element->height);
}

void render_element(Element element)
{
    round_values(&element);
    SDL_Rect dest = {(int)element.pos.x, (int)element.pos.y, (int)element.width, (int)element.height};
    if(element.type == BUTTON || element.type == IMAGE)
        render_button(element, dest);
    SDL_Color white = {255,255,255,128};
    if(strlen(element.text) > 0)
        render_menu_text(dest, tFONT_1, element.text, white);
}

void render_score(Element element)
{
    round_values(&element);
    SDL_Color white = {255,255,255,128};
    render_player_text(element.pos, element.text, white);
}

void render_main()
{
    render_element(t_main_title);
    render_element(b_start);
    render_element(b_board);
}

void render_start()
{
    render_element(t_number_of_players);
    render_element(t_singleplayer);
    render_element(t_cooperative);
    render_element(r_one_player);
    render_element(r_two_player);
    render_element(t_which_map);
    render_element(i_map_one);
    render_element(i_map_two);
    render_element(r_map_one);
    render_element(r_map_two);
    render_element(b_play);
}

void render_board()
{
    render_element(t_board_title);
    for(int i=0;i<5;i++) {
        if(strcmp(t_score[i].text,"0") != 0) {
            render_score(t_name[i]);
            render_score(t_score[i]);
        }
    }
    render_element(b_back);
}

void render_menu()
{
    if(in_main)
        render_main();
    else if(in_board)
        render_board();
    else if(in_start)
        render_start();
}

bool mouse_is_over(Element element)
{
    if(   element.pos.x-element.width/2  < mouse_x && element.pos.x+element.width/2  > mouse_x
          && element.pos.y-element.height/2 < mouse_y && element.pos.y+element.height/2 > mouse_y)
        return true;
    return false;
}

void set_button_texture(Element *element)
{
    if(mouse_is_over(*element))
        element->textureNumber = tBUTTON_OVER;
    else
        element->textureNumber = tBUTTON;
}

void set_radio_texture(Element *element)
{
    if(mouse_is_over(*element))
        element->textureNumber = tBUTTON_RADIO_OVER;
    else
    if(element->active)
        element->textureNumber = tBUTTON_RADIO_ON;
    else
        element->textureNumber= tBUTTON_RADIO_OFF;
}

void handle_main_mouseover()
{
    set_button_texture(&b_start);
    set_button_texture(&b_board);
}

void handle_start_mouseover()
{
    set_radio_texture(&r_one_player);
    set_radio_texture(&r_two_player);
    set_radio_texture(&r_map_one);
    set_radio_texture(&r_map_two);
    set_button_texture(&b_play);
}

void handle_board_mouseover()
{
    set_button_texture(&b_back);
}

void handle_mouseover()
{
    if(in_main)
        handle_main_mouseover();
    else if(in_start)
        handle_start_mouseover();
    else if(in_board)
        handle_board_mouseover();
}

void handle_main_clicks()
{
    if(b_start.textureNumber == tBUTTON_OVER) {
        in_main = false;
        in_start = true;
    } else if(b_board.textureNumber == tBUTTON_OVER) {
        in_main = false;
        in_board = true;
    }
}

void handle_start_clicks(bool *play)
{
    if(r_one_player.textureNumber == tBUTTON_RADIO_OVER) {
        r_one_player.active = true;

        if(r_two_player.active)
            r_two_player.active = false;
    } else if(r_two_player.textureNumber == tBUTTON_RADIO_OVER) {
        r_two_player.active = true;
        if(r_one_player.active)
            r_one_player.active = false;
    } else if(r_map_one.textureNumber == tBUTTON_RADIO_OVER) {
        r_map_one.active = true;
        if(r_map_two.active)
            r_map_two.active = false;
    } else if(r_map_two.textureNumber == tBUTTON_RADIO_OVER) {
        r_map_two.active = true;
        if(r_map_one.active)
            r_map_one.active = false;
    } else if(b_play.textureNumber == tBUTTON_OVER)  {
        if(r_one_player.active)
            player_two_active = false;
        else
            player_two_active = true;
        if(r_map_one.active)
            map_type = GRASS;
        else
            map_type = WOOD;
        in_start = false;
        *play = true;
    }
}

void handle_board_clicks()
{
    if(b_back.textureNumber == tBUTTON_OVER) {
        in_board = false;
        in_main = true;
    }
}

void handle_clicks(bool *play)
{
    if(in_main)
        handle_main_clicks();
    else if(in_start)
        handle_start_clicks(play);
    else if(in_board)
        handle_board_clicks();
}