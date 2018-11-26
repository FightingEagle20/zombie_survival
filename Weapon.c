//
// Created by Patrick on 2018-11-04.
//

#include "Weapon.h"

#include "Globals.h"

// when adding a new weapon, edit: Weapon.c/.h, Entity.c, Projectiles.c, Textures.c/.h

//                            NoWeapon Pistol Uzi Sniper  RPG
int const widths[]            = {  22,     29,  35,   39,   39};
int const heights[]           = {  42,     17,  17,   17,   16};
int const damage[]            = {  10,     25,  15,  100,   75};
uint32_t const fire_speeds[]  = {1500,    500,  50, 1000, 1000};

GameTextureNumber get_weapon_texture_number(UnitID unit_id, WeaponNumber weapon_number)
{
    if(weapon_number == NO_WEAPON) {
        if(unit_id == uZOMBIE_BASIC) {
            return tZOMBIE_NO_WEAPON;
        } else {
            printf("Error: Tried to get the texture_number of NO_WEAPON while not a zombie in get_weapon_texture_number!");
            printf("unit_id = %d ",unit_id);
            printf("weapon_number = %d\n",weapon_number);
        }
    }
    if(unit_id == uPLAYER_ONE || unit_id == uPLAYER_TWO) {
        return tSOLDIER_PISTOL + weapon_number - 1;
    } else {
        printf("Error: Tried to get the texture_number of a weapon while not a player in get_weapon_texture_number!");
        printf("unit_id = %d ",unit_id);
        printf("weapon_number = %d\n",weapon_number);
    }
    printf("Error: Couldn't find texture_number for weapon in get_weapon_texture_number! -- ");
    printf("unit_id = %d ",unit_id);
    printf("weapon_number = %d\n",weapon_number);
    return -1;
}

void setup_weapon(Weapon *weapon, WeaponNumber weapon_number, UnitID unit_id)
{
    weapon->width = widths[weapon_number];
    weapon->height = heights[weapon_number];
    weapon->weapon_number = weapon_number;
    weapon->texture_number = get_weapon_texture_number(unit_id, weapon_number);
    weapon->damage = damage[weapon_number];
    weapon->fire_speed = fire_speeds[weapon_number];
    weapon->last_time_fired = 0;
}