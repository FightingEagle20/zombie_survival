//
// Created by Patrick on 2018-10-22.
//

#ifndef ZOMBIE_SURVIVAL_PLAYER_H
#define ZOMBIE_SURVIVAL_PLAYER_H

#include "Globals.h"
#include "Entity.h"
#include "Zombie.h"

void player_setup(Entity *player, GameTextureNumber texture_number, UnitID player_id);
void player_handle_input(Entity *player);
void shoot_player(Entity *player);
void damage_player(Entity *player, int damage, bool *quit);
void move_player(Entity *player);
void render_player(Entity *player);

void move_player_projectiles(Zombie *zombies);
void render_player_projectiles();
void free_projectiles();

#endif //ZOMBIE_SURVIVAL_PLAYER_H
