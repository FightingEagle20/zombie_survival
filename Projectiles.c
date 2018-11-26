//
// Created by Patrick on 2018-11-07.
//

#include "Projectiles.h"
#include "Zombie.h"
#include "Timer.h"

//                        NoWeapon Pistol Uzi Sniper  RPG
int const width[]         = {0,      48,  40,   52,   64};
int const height[]        = {0,      48,  40,   52,   64};
int const speed[]         = {0,     600, 600, 2000,  600};
double const relative_x[] = {0,       1,   1,    1,    1};
double const relative_y[] = {0,     0.2, 0.2,  0.2,  0.2};

void setup_projectile(Projectile *projectile, Entity player)
{
    WeaponNumber num = player.weapon.weapon_number;
    projectile->weapon_number = num;

    set_relative_pos(&projectile->pos,player,relative_x[num],relative_y[num]);

    projectile->vel.x  = (int)round( cos( angle(player.direction)*M_PI/180.0 )*speed[num] );
    projectile->vel.y  = (int)round( sin( angle(player.direction)*M_PI/180.0 )*speed[num] );

    projectile->width  = width[num];
    projectile->height = height[num];

    projectile->damage = player.weapon.damage;
}

void new_projectile(Projectile **projectiles, Entity player)
{
    Projectile *new_projectile = (Projectile*)malloc(sizeof(Projectile));
    if(new_projectile != NULL) {
        setup_projectile(new_projectile,player);
        new_projectile->next = *projectiles;
        *projectiles = new_projectile;
    } else {
        printf("Unable to allocate memory for new_projectile in new_projectile!\n");
    }
}

bool out_of_bounds(Projectile *projectile)
{
    if(projectile->pos.x < 0 || projectile->pos.x > SCREEN_WIDTH)
        return true;
    if(projectile->pos.y < 0 || projectile->pos.y > SCREEN_HEIGHT)
        return true;
    return false;
}

Entity* collided(Projectile *projectile, Zombie zombies)
{
    for(int i=0;i<zombies.zombie_count;i++) {
        Entity *zombie = &zombies.zombie[i];
        if( (projectile->pos.x >= zombie->pos.x-(double)zombie->width/2 && projectile->pos.x <= zombie->pos.x+(double)zombie->width/2)
            && ((projectile->pos.y >= zombie->pos.y-(double)zombie->height/2 && projectile->pos.y <= zombie->pos.y+(double)zombie->height/2))) {
            return zombie;
        }
    }
    return NULL;
}

void move_projectiles(Projectile **projectiles, Zombie *zombies)
{
    uint32_t time_passed = get_timePassed();
    Projectile *iter, *prev = NULL, *next;
    for(iter=*projectiles;iter!=NULL;iter=next) {
        next = iter->next;
        iter->pos.x += iter->vel.x * (time_passed/1000.f);
        iter->pos.y += iter->vel.y * (time_passed/1000.f);
        Entity *hit = collided(iter,*zombies);
        if(out_of_bounds(iter) || hit != NULL ) {
            if(iter->weapon_number == RPG)
                damage_zombies_around(zombies,iter->pos,iter->damage);
            else
                damage_zombie_killed(zombies,hit,iter->damage);
            if(prev == NULL) {
                *projectiles = iter->next;
            } else {
                prev->next = iter->next;
            }
            free(iter);
            iter = NULL;
        }
        if(iter != NULL)
            prev = iter;
    }
}

GameTextureNumber get_bullet_tnumber(Projectile *projectile)
{
    return tBULLET_PISTOL+projectile->weapon_number-1;
}

void render_projectiles(Projectile *projectiles)
{
    Projectile *iter;
    for(iter=projectiles;iter!=NULL;iter=iter->next) {
        int original_x = (int)round(iter->pos.x-(double)iter->width/2);
        int original_y = (int)round(iter->pos.y-(double)iter->height/2);
        SDL_Rect dest = {original_x,original_y,iter->width,iter->height};
        SDL_RenderCopy(renderer, get_game_texture(get_bullet_tnumber(iter)),NULL,&dest);
    }
}

void freeup_projectiles(Projectile **projectiles)
{
    Projectile *iter, *next;
    for(iter=*projectiles;iter!=NULL;iter=next) {
        next = iter->next;
        free(iter);
    }
    *projectiles = NULL;
}
