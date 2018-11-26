//
// Created by Patrick on 2018-11-04.
//

#ifndef ZOMBIE_SURVIVAL_WEAPON_H
#define ZOMBIE_SURVIVAL_WEAPON_H

#include "Textures.h"

typedef struct Weapon{
    int width, height;

    WeaponNumber weapon_number;
    GameTextureNumber texture_number;

    int damage;
    int fire_speed;
    uint32_t last_time_fired;
}Weapon;

void setup_weapon(Weapon *weapon, WeaponNumber weapon_number, UnitID unit_id);

#endif //ZOMBIE_SURVIVAL_WEAPON_H
