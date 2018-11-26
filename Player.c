//
// Created by Patrick on 2018-10-22.
//

#include "Player.h"

#include "Globals.h"
#include "Textures.h"
#include "Projectiles.h"
#include "Zombie.h"
#include "Timer.h"
#include "Loot.h"

int const player_width = 36;
int const player_height = 43;
int const player_speed = 200;
int const player_health = 100;

enum Key{KEY_UP,KEY_LEFT,KEY_DOWN,KEY_RIGHT,KEY_SHOOT,KEY_PREV,KEY_NEXT};

typedef enum WeaponSwitch{NEXT,PREV}WeaponSwitch;

// variables that only players use
bool player_key_is_down[2][5];  // 4 movement + 1 for shooting
Projectile *projectiles = NULL;

void player_setup(Entity *player, GameTextureNumber texture_number, UnitID player_id)
{
    player->width = player_width;
    player->height = player_height;
    player->pos.x = (double)SCREEN_WIDTH/2-(double)player->width/2;
    player->pos.y = (double)SCREEN_HEIGHT/2-(double)player->height/2;
    player->next_pos  = player->pos;
    player->vel = (Coordinate){0, 0};
    player->speed = player_speed;
    player->health = player_health;
    player->damaged = false;
    player->start_of_damage = 0;
    player->entity_texture = texture_number;
    player->direction = RIGHT;
    player->unit_id = player_id;
    setup_weapon(&player->weapon,PISTOL,player->unit_id);
    for(int i = 0;i<5;i++) {
        player_key_is_down[player->unit_id][i] = false;
    }
}

bool key_is(Entity *player, int key_index)
{
    int const keyboard_layout[2][7] = {{SDLK_w,SDLK_a,SDLK_s,SDLK_d,SDLK_j,SDLK_k,SDLK_l},
                                       {SDLK_UP,SDLK_LEFT,SDLK_DOWN,SDLK_RIGHT,SDLK_KP_1,SDLK_KP_2,SDLK_KP_3}};
    return (event.key.keysym.sym == keyboard_layout[player->unit_id][key_index]);
}

void set_key_state(Entity *player, int index, bool new_state)
{
    player_key_is_down[player->unit_id][index] = new_state;
}

void set_weapon(Entity *player, WeaponSwitch weapon_switch)
{
    WeaponNumber weapon_number = player->weapon.weapon_number;
    if(weapon_switch == NEXT) {
        weapon_number++;
        if(weapon_number >= number_of_weapons)
            weapon_number = PISTOL;
    } else {
        weapon_number--;
        if(weapon_number <= NO_WEAPON)
            weapon_number = number_of_weapons-1;
    }
    setup_weapon(&player->weapon,weapon_number,player->unit_id);
}

void player_handle_input(Entity *player)
{
    if(event.type == SDL_KEYDOWN) {
        if(key_is(player,KEY_UP)) {
            player->vel.y = -player->speed;
            set_key_state(player,KEY_UP,true);
        } else if(key_is(player,KEY_DOWN)) {
            player->vel.y = player->speed;
            set_key_state(player,KEY_DOWN,true);
        } else if(key_is(player,KEY_LEFT)) {
            player->vel.x = -player->speed;
            set_key_state(player,KEY_LEFT,true);
        } else if(key_is(player,KEY_RIGHT)) {
            player->vel.x = player->speed;
            set_key_state(player,KEY_RIGHT,true);
        } else if(key_is(player,KEY_SHOOT)) {
            set_key_state(player,KEY_SHOOT,true);
        } else if(key_is(player,KEY_NEXT)) {
            set_weapon(player,NEXT);
        } else if(key_is(player,KEY_PREV)) {
            set_weapon(player,PREV);
        }
    } else if(event.type == SDL_KEYUP) {
        if(key_is(player,KEY_UP)) {
            if(player_key_is_down[player->unit_id][KEY_DOWN]) {
                player->vel.y = player->speed;
            } else {
                player->vel.y = 0;
            }
            set_key_state(player,KEY_UP,false);
        } else if(key_is(player,KEY_DOWN)) {
            if(player_key_is_down[player->unit_id][KEY_UP]) {
                player->vel.y = -player->speed;
            } else {
                player->vel.y = 0;
            }
            set_key_state(player,KEY_DOWN,false);
        } else if(key_is(player,KEY_LEFT)) {
            if(player_key_is_down[player->unit_id][KEY_RIGHT]) {
                player->vel.x = player->speed;
            } else {
                player->vel.x = 0;
            }
            set_key_state(player,KEY_LEFT,false);
        } else if(key_is(player,KEY_RIGHT)) {
            if(player_key_is_down[player->unit_id][KEY_LEFT]) {
                player->vel.x = -player->speed;
            } else {
                player->vel.x = 0;
            }
            set_key_state(player,KEY_RIGHT,false);
        } else if(key_is(player,KEY_SHOOT)) {
            set_key_state(player,KEY_SHOOT,false);
        }
    }
}

void shoot_player(Entity *player)
{
    uint32_t time_passed = get_currentTick()-player->weapon.last_time_fired;
    WeaponNumber num = player->weapon.weapon_number;
    int number_of_bullets = get_player_bullet_count(player->unit_id,num);

    if(player_key_is_down[player->unit_id][KEY_SHOOT] && player->weapon.fire_speed < time_passed) {
        if(number_of_bullets > 0 || num == PISTOL) {
            if(num == SNIPER)
                for(int i=0;i<3;i++)
                    new_projectile(&projectiles,*player);

            new_projectile(&projectiles,*player);
            if(num != PISTOL)
                dec_player_bullet_count(player->unit_id,num);
            player->weapon.last_time_fired = get_currentTick();
        } else {
            /*Out of ammo*/
        }
    }
}

void damage_player(Entity *player, int damage, bool *quit)
{
    player->health -= damage;
    if(player->health <= 0) {
        *quit = true;
    }
}

void check_loot_pickup(Entity *player)
{
    LootType loot_type = player_loot_collision(player->pos);
    if(loot_type != NO_LOOT)
        add_player_bullet_count(player->unit_id,(WeaponNumber)loot_type,get_bullet_loot_amount(loot_type));
}

void move_player(Entity *player)
{
    uint32_t time_passed = get_timePassed();

    player->next_pos.x += player->vel.x * (time_passed/1000.f);
    if(player->next_pos.x+(double)player->width/2 > SCREEN_WIDTH) {
        player->next_pos.x = SCREEN_WIDTH - (double)player->width/2;
    } else if(player->next_pos.x-(double)player->width/2 < 0) {
        player->next_pos.x = (double)player->width/2;
    }

    player->next_pos.y += player->vel.y * (time_passed/1000.f);
    if(player->next_pos.y+(double)player->height/2 > SCREEN_HEIGHT) {
        player->next_pos.y = SCREEN_HEIGHT - (double)player->height/2;
    } else if(player->next_pos.y-(double)player->height/2 < 0) {
        player->next_pos.y = (double)player->height/2;
    }

    check_loot_pickup(player);
}

void render_player(Entity *player)
{
    player->pos = player->next_pos;
    render_e(player);
}

void move_player_projectiles(Zombie *zombies)
{
    move_projectiles(&projectiles, zombies);
}

void render_player_projectiles()
{
    render_projectiles(projectiles);
}

void free_projectiles()
{
    freeup_projectiles(&projectiles);
}