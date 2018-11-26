//
// Created by Patrick on 2018-11-11.
//

#ifndef ZOMBIE_SURVIVAL_LOOT_H
#define ZOMBIE_SURVIVAL_LOOT_H

#include "Textures.h"

typedef struct Loot{
    Coordinate pos;
    int radius;
    LootType loot_type;
    GameTextureNumber texture_number;

    struct Loot *next;
}Loot;

void spawn_loot(Coordinate pos);
LootType player_loot_collision(Coordinate player_pos);

int get_bullet_loot_amount(LootType loot_type);
int get_player_bullet_count(UnitID unit_id, WeaponNumber weapon_number);
void add_player_bullet_count(UnitID unit_id, WeaponNumber weapon_number,int amount);
void dec_player_bullet_count(UnitID unit_id, WeaponNumber weapon_number);

void render_all_loot();
void free_all_loot();

#endif //ZOMBIE_SURVIVAL_LOOT_H
