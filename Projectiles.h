//
// Created by Patrick on 2018-11-07.
//

#ifndef ZOMBIE_SURVIVAL_PROJECTILE_H
#define ZOMBIE_SURVIVAL_PROJECTILE_H

#include "Weapon.h"
#include "Entity.h"
#include "Zombie.h"

typedef struct Projectile{
    Coordinate pos;
    Coordinate vel;
    int width, height;
    WeaponNumber weapon_number;
    int damage;

    struct Projectile *next;
}Projectile;

void new_projectile(Projectile **projectiles, Entity player);
void move_projectiles(Projectile **projectiles, Zombie *zombies);
void render_projectiles(Projectile *projectiles);
void freeup_projectiles(Projectile **projectiles);

#endif //ZOMBIE_SURVIVAL_PROJECTILE_H
