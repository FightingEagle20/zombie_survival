//
// Created by Patrick on 2018-11-11.
//

#include "Loot.h"

#include "Globals.h"

//                          NO_LOOT PISTOL UZI SNIPER RPG
int const loot_radius[]   = {0,       0,    14,  16,  20};
int const bullet_amount[] = {0,       0,   500,  10,   5};

int const loot_pickup_radius = 30;

int player_bullet_count[2][5] = {0};  // NO_WEAPON  + 4 weapons

Loot *first = NULL;

void setup_loot(Loot *loot, Coordinate pos)
{
    loot->pos.x = (int)round(pos.x);
    loot->pos.y = (int)round(pos.y);
    int type = rand()%3 + 2;
    loot->radius = loot_radius[type];
    loot->loot_type = type;
    loot->texture_number = tLOOT_UZI+(type-2);
}

void spawn_loot(Coordinate pos)
{
    Loot *new_loot = (Loot*)malloc(sizeof(Loot));
    if(new_loot != NULL) {
        setup_loot(new_loot,pos);
        new_loot->next = first;
        first = new_loot;
    } else {
        printf("Error: Unable to allocate memory for new_loot in spawn_loot!\n");
    }
}

LootType player_loot_collision(Coordinate pos)
{
    Loot *prev = NULL;
    for(Loot *iter=first;iter!=NULL;iter=iter->next) {
        if(distance(pos,iter->pos) <= loot_pickup_radius) {
            if(prev == NULL)
                first = iter->next;
            else
                prev->next = iter->next;
            LootType loot_type  = iter->loot_type;
            free(iter);
            return loot_type;
        }
        prev = iter;
    }
    return NO_LOOT;
}

int get_bullet_loot_amount(LootType loot_type)
{
    return bullet_amount[loot_type];
}

int get_player_bullet_count(UnitID unit_id, WeaponNumber weapon_number)
{
    return player_bullet_count[unit_id][weapon_number];
}

void add_player_bullet_count(UnitID unit_id, WeaponNumber weapon_number,int amount)
{
    player_bullet_count[unit_id][weapon_number] += amount;
}

void dec_player_bullet_count(UnitID unit_id, WeaponNumber weapon_number)
{
    player_bullet_count[unit_id][weapon_number]--;
}

void render_all_loot()
{
    for(Loot *iter = first; iter != NULL; iter = iter->next) {
        int original_x = (int)iter->pos.x-iter->radius;
        int original_y = (int)iter->pos.y-iter->radius;
        SDL_Rect dest = {original_x, original_y, iter->radius*2, iter->radius*2};
        SDL_RenderCopy(renderer, get_game_texture(iter->texture_number),NULL,&dest);
    }
}
void free_all_loot()
{
    Loot **iter, *next;
    for(iter=&first;*iter!=NULL;*iter=next) {
        next = (*iter)->next;
        free(*iter);
        *iter = NULL;
    }
}