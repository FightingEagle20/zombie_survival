//
// Created by Patrick on 2018-10-27.
//

#include <float.h>
#include "Globals.h"
#include "Zombie.h"
#include "Pathfinding.h"
#include "Timer.h"
#include "Projectiles.h"
#include "Loot.h"

#include "Player.h"

int const zombie_width = 36;
int const zombie_height = 43;
int const zombie_speed = 50;
int const zombie_health = 100;

int const zombie_attack_radius = 50;

uint32_t last_spawned = 0;

void zombie_setup(Entity *zombie, Coordinate pos, GameTextureNumber zombie_texture, UnitID zombie_id)
{
    zombie->width = zombie_width;
    zombie->height = zombie_height;
    zombie->pos = pos;
    zombie->next_pos  = zombie->pos;
    zombie->vel.x = 0;
    zombie->vel.y = 0;
    zombie->speed = zombie_speed;
    zombie->health = zombie_health;
    zombie->damaged = false;
    zombie->start_of_damage = 0;
    zombie->entity_texture = zombie_texture;
    zombie->direction = RIGHT;
    zombie->unit_id = zombie_id;
    setup_weapon(&zombie->weapon,NO_WEAPON,zombie->unit_id);
}

void spawn_zombie(Zombie *zombies, Coordinate pos, GameTextureNumber texture_number, UnitID zombie_id)
{
    Entity *new_zombies = (Entity*)malloc(sizeof(Entity)*(zombies->zombie_count+1));
    if(new_zombies == NULL) {
        printf("Error: Couldn't allocate memory for **new_zombies in spawn_zombie!\n");
    } else {
        for(int i=0;i<zombies->zombie_count;i++) {
            new_zombies[i] = zombies->zombie[i];
        }
        Entity *new_zombie = (Entity*)malloc(sizeof(Entity));
        if(new_zombie == NULL) {
            printf("Error: Couldn't allocate memory for *new_zombie in spawn_zombie!\n");
        } else {
            zombie_setup(new_zombie, pos, texture_number, zombie_id);
            new_zombies[zombies->zombie_count] = *new_zombie;
            free(new_zombie);
            zombies->zombie_count++;
            if(zombies->zombie != NULL)
                free(zombies->zombie);
            zombies->zombie = new_zombies;
        }
    }
}

void spawn_zombie_logic(Zombie *zombies, uint32_t spawn_interval)
{
    int padding = 2*ZOMBIE_PRECISION;
    int defined_x[2] = {padding,SCREEN_WIDTH-padding};
    if(get_currentTick()-last_spawned > spawn_interval) {
        int index = rand()%2;
        Coordinate pos;
        pos.x = defined_x[index];
        pos.y = rand()%((SCREEN_HEIGHT/ZOMBIE_PRECISION)-2) * ZOMBIE_PRECISION + padding;

        spawn_zombie(zombies,pos,tZOMBIE_BASIC_STAND,uZOMBIE_BASIC);
        last_spawned = get_currentTick();
    }
}

void set_vel(Entity *zombie)
{
    if(zombie->next_pos.x-zombie->pos.x > 0)
        zombie->vel.x = zombie->speed;
    else if(zombie->next_pos.x-zombie->pos.x < 0)
        zombie->vel.x = -zombie->speed;
    else
        zombie->vel.x = 0;

    if(zombie->next_pos.y-zombie->pos.y > 0)
        zombie->vel.y = zombie->speed;
    else if(zombie->next_pos.y-zombie->pos.y < 0)
        zombie->vel.y = -zombie->speed;
    else
        zombie->vel.y = 0;
}

bool within(double coordinate1, double within_value, double coordinate2)
{
    if(coordinate1 <= within_value && within_value <= coordinate2)
        return true;
    if(coordinate2 <= within_value && within_value <= coordinate1)
        return true;
    return false;
}

void precise_movement(Entity *zombie)
{
    uint32_t time_passed = get_timePassed();
    Coordinate prev_pos = zombie->pos;
    zombie->pos.x += zombie->vel.x * (time_passed/1000.f);
    zombie->pos.y += zombie->vel.y * (time_passed/1000.f);
    if(within(prev_pos.x,zombie->next_pos.x,zombie->pos.x) && within(prev_pos.y,zombie->next_pos.y,zombie->pos.y))
        zombie->pos = zombie->next_pos;
}

bool fequal(double d1, double d2)
{
    double epsilon = 0.001; // some small value
    return fabs(d1-d2) < epsilon;
}

bool at_next_pos(Entity *zombie)
{
    if(fequal(zombie->pos.x,zombie->next_pos.x) && fequal(zombie->pos.y,zombie->next_pos.y)) {
        zombie->pos = zombie->next_pos;
        return true;
    }
    return false;
}

void attack_zombie(Entity *zombie, Entity *player1, Entity *player2, bool *quit)
{
    uint32_t current_tick = get_currentTick();
    if(current_tick-zombie->weapon.last_time_fired >= zombie->weapon.fire_speed ) {
        double distance1 = distance(zombie->pos,player1->pos);
        double distance2;
        if(player_two_active)
            distance2 = distance(zombie->pos,player2->pos);
        else
            distance2 = DBL_MAX;
        if(distance1 < distance2 && distance1 < zombie_attack_radius) {
            damage_player(player1,zombie->weapon.damage,quit);
            zombie->weapon.last_time_fired = current_tick;
        } else if(distance2 < zombie_attack_radius) {
            damage_player(player2, zombie->weapon.damage,quit);
            zombie->weapon.last_time_fired = current_tick;
        }
    }
}

void move_zombies(Zombie zombies, Entity *player1, Entity *player2, bool *quit)
{
    for(int i=0;i<zombies.zombie_count;i++) {
        if(at_next_pos(&zombies.zombie[i])) {
            find_path(&zombies.zombie[i], player1, player2);
            set_vel(&zombies.zombie[i]);
        }
        precise_movement(&zombies.zombie[i]);
        attack_zombie(&zombies.zombie[i], player1, player2, quit);
    }
}

void render_zombies(Zombie *zombies)
{
    for(int i=0;i<zombies->zombie_count;i++) {
        render_e(&zombies->zombie[i]);
    }
}

void kill_zombie(Zombie *zombies, Entity *zombie)
{
    Entity *new_zombies = (Entity*) malloc(sizeof(Entity)*(zombies->zombie_count-1));
    if(new_zombies == NULL) {
        printf("Error: Couldn't allocate memory for **new_zombies in kill_zombie!\n");
    } else {
        for(int i=0,j=0;i<zombies->zombie_count;i++) {
            if(&zombies->zombie[i] != zombie) {
                new_zombies[j] = zombies->zombie[i];
                j++;
            }
        }
        zombies->zombie_count--;
        if(rand()%5 == 0)
            spawn_loot(zombie->pos);
        free(zombies->zombie);
        zombies->zombie = new_zombies;
    }
}

bool damage_zombie_killed(Zombie *zombies, Entity *zombie, int damage)
{
    if(zombie != NULL) {
        zombie->health -= damage;
        zombie->damaged = true;
        zombie->start_of_damage = get_currentTick();
        if(zombie->health <= 0) {
            kill_zombie(zombies,zombie);
            return true;
        }
    }
    return false;
}

void damage_zombies_around(Zombie *zombies, Coordinate projectile_pos, int damage)
{
    int explosion_radius = 150;
    for(int i=0;i<zombies->zombie_count;i++) {
        Entity *current_zombie = &zombies->zombie[i];
        if(distance(projectile_pos,current_zombie->pos) < explosion_radius)
            if(damage_zombie_killed(zombies,current_zombie,damage))
                i--;
    }
}

void free_zombies(Zombie *zombies)
{
    free(zombies->zombie);
}
