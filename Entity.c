//
// Created by Patrick on 2018-10-25.
//

#include "Entity.h"

#include "Globals.h"
#include "Textures.h"
#include "Timer.h"

uint32_t const damagedInterval = 50;
uint32_t const zombie_attack_interval = 200;

//                           NoWeapon  Pistol    Uzi  Sniper  RPG
double const weaponRatioX[] = {0.3,       0.45,   0.55,   0.6,  0.6};
double const weaponRatioY[] = {0,       0.25,   0.25,  0.25, 0.25};


void set_direction(Entity *entity)
{
    Coordinate position;
    Direction directionMatrix[3][3] = {{  UP_LEFT,  UP,  UP_RIGHT},
                                       {     LEFT,   0,     RIGHT},
                                       {DOWN_LEFT,DOWN,DOWN_RIGHT}};

    if(entity->vel.x > 0)        position.x = 2;
    else if(entity->vel.x == 0)  position.x = 1;
    else                         position.x = 0;

    if(entity->vel.y > 0)        position.y = 2;
    else if(entity->vel.y == 0)  position.y = 1;
    else                         position.y = 0;

    if(position.x != 1 || position.y != 1) {
        entity->direction = directionMatrix[(int)position.y][(int)position.x];
    }
}

int angle(Direction direction)
{
    return (direction*45);
}

void set_relative_pos(Coordinate *pos, Entity entity, double ratio_x, double ratio_y)
{
    // in this function everything works as if the y axis's zero point was in the bottom left corner
    // this is because of the two formulas at the end of this function
    // and this is why we subtract one line below this comment
    double before_rotation_x = entity.pos.x - entity.width*ratio_x;
    double before_rotation_y = entity.pos.y - entity.height*ratio_y;
    double center_x = entity.pos.x;
    double center_y = entity.pos.y;
    double weapon_angle = angle(entity.direction) * M_PI/180.0;
    double translated_x = before_rotation_x-center_x;
    double translated_y = before_rotation_y-center_y;
    pos->x = center_x - (translated_x)*cos(weapon_angle) + (translated_y)*sin(weapon_angle);
    pos->y = center_y - (translated_x)*sin(weapon_angle) - (translated_y)*cos(weapon_angle);
}

void render_e(Entity *entity)
{
    set_direction(entity);

    uint32_t current_tick = get_currentTick();

    if(entity->weapon.weapon_number > NO_WEAPON || current_tick-entity->weapon.last_time_fired <= zombie_attack_interval) {
        Coordinate weapon_pos;
        WeaponNumber num = entity->weapon.weapon_number;
        set_relative_pos(&weapon_pos, *entity, weaponRatioX[num], weaponRatioY[num]);
        int original_weapon_x = (int)round(weapon_pos.x - (double)entity->weapon.width/2);
        int original_weapon_y = (int)round(weapon_pos.y - (double)entity->weapon.height/2);
        SDL_Rect dest_weapon = {original_weapon_x,original_weapon_y,entity->weapon.width,entity->weapon.height};
        SDL_RenderCopyEx(renderer, get_game_texture(entity->weapon.texture_number),NULL,&dest_weapon,angle(entity->direction),NULL,SDL_FLIP_NONE);
    }

    int original_x = (int)round( entity->pos.x - (double)entity->width/2 );
    int original_y = (int)round( entity->pos.y - (double)entity->height/2 );
    SDL_Rect dest_entity = {original_x,original_y,entity->width,entity->height};
    SDL_RenderCopyEx(renderer, get_game_texture(entity->entity_texture),NULL,&dest_entity,angle(entity->direction),NULL,SDL_FLIP_NONE);

    if(entity->damaged) {
        SDL_RenderCopyEx(renderer, get_game_texture(tENTITY_DAMAGED),NULL,&dest_entity,angle(entity->direction),NULL,SDL_FLIP_NONE);
        if(current_tick-entity->start_of_damage >= damagedInterval)
            entity->damaged = false;
    }
}
