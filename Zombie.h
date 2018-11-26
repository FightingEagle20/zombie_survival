//
// Created by Patrick on 2018-10-27.
//

#ifndef ZOMBIE_SURVIVAL_ZOMBIE_H
#define ZOMBIE_SURVIVAL_ZOMBIE_H

#include "Entity.h"

typedef struct Zombie{
    Entity *zombie; // array of pointers
    int zombie_count;
}Zombie;

void spawn_zombie_logic(Zombie *zombies, uint32_t spawn_interval);
bool damage_zombie_killed(Zombie *zombies, Entity *zombie, int damage);
void damage_zombies_around(Zombie *zombies, Coordinate projectile_pos, int damage);
void move_zombies(Zombie zombies, Entity *player1, Entity *player2, bool *quit);
void render_zombies(Zombie *zombies);

void free_zombies(Zombie *zombies);

#endif //ZOMBIE_SURVIVAL_ZOMBIE_H
