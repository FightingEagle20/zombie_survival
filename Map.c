//
// Created by Patrick on 2018-10-27.
//

#include "Map.h"

#include "Globals.h"
#include "Textures.h"

void load_map()
{
    FILE *f;
    f = fopen("maps/map_01","r");
    for(int i=0;i<MAP_SIZE;i++) {
        for(int j=0;j<MAP_SIZE;j++) {
            fscanf(f,"%d",&map[i][j]);
        }
    }
    fclose(f);
}

void render_map()
{
    for(int i=0;i<MAP_SIZE;i++) {
        for(int j=0;j<MAP_SIZE;j++) {
            GameTextureNumber current_texture = -1;
            if(map_type == GRASS) {
                switch(map[i][j]) {
                    case 1: current_texture = tGRASS_TILE_1; break;
                    case 2: current_texture = tGRASS_TILE_2; break;
                    case 3: current_texture = tGRASS_TILE_3; break;
                    case 4: current_texture = tGRASS_TILE_4; break;
                    default:
                        printf("Error in map loading! Unhandled option!\n");
                        current_texture = tGRASS_TILE_1;
                        break;
                }
            } else if(map_type == WOOD) {
                switch(map[i][j]) {
                    case 1: current_texture = tWOOD_TILE_1; break;
                    case 2: current_texture = tWOOD_TILE_2; break;
                    case 3: current_texture = tWOOD_TILE_3; break;
                    case 4: current_texture = tWOOD_TILE_4; break;
                    default:
                        printf("Error in map loading! Unhandled option!\n");
                        current_texture = tWOOD_TILE_1;
                        break;
                }
            } else {
                printf("Error: No such map_type in render map!\n");
            }
            SDL_Rect dest = {j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if(current_texture != -1)
                SDL_RenderCopy(renderer, get_game_texture(current_texture),NULL,&dest);
        }
    }
}