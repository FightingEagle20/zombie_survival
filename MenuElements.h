//
// Created by Patrick on 2018-11-25.
//

#ifndef ZOMBIE_SURVIVAL_MENUELEMENTS_H
#define ZOMBIE_SURVIVAL_MENUELEMENTS_H

#include "Globals.h"
#include "Textures.h"

typedef enum ElementType{TEXT,IMAGE,BUTTON}ElementType;

typedef struct Element{
    Coordinate pos;
    double width, height;
    char text[100+1];
    bool active;
    ElementType type;
    MenuTextureNumber textureNumber;
}Element;

int mouse_x, mouse_y;

void set_in_main();
void setup_elements();
void handle_mouseover();
void handle_clicks(bool *play);
void render_menu();

#endif //ZOMBIE_SURVIVAL_MENUELEMENTS_H
