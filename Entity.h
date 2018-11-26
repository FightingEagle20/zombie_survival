//
// Created by Patrick on 2018-10-25.
//

#ifndef ZOMBIE_SURVIVAL_ENTITY_H
#define ZOMBIE_SURVIVAL_ENTITY_H

#include "Globals.h"
#include "Textures.h"
#include "Weapon.h"

typedef enum Direction{RIGHT,DOWN_RIGHT,DOWN,DOWN_LEFT,LEFT,UP_LEFT,UP,UP_RIGHT}Direction;

typedef struct Entity{
    Coordinate pos, next_pos;
    Coordinate vel;
    int width, height;
    int speed;
    int health;
    bool damaged;
    uint32_t start_of_damage;
    GameTextureNumber entity_texture;
    Direction direction;
    UnitID unit_id;
    Weapon weapon;
}Entity;

int angle(Direction direction);
void set_relative_pos(Coordinate *pos, Entity entity, double ratio_x, double ratio_y);

void render_e(Entity *entity);

#endif //ZOMBIE_SURVIVAL_ENTITY_H
