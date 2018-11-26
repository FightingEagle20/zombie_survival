//
// Created by Patrick on 2018-10-27.
//

#include "Pathfinding.h"

#include <limits.h> // for INT_MAX
#include <float.h>  // for DBL_MAX

#include "Globals.h"
#include "Entity.h"

typedef struct Node{
    Coordinate pos;

    bool in_open_set;
    bool in_closed_set;

    bool walkable;

    double g_cost;
    double f_cost;

    Coordinate parent;
}Node;

int height_of_node;
int width_of_node;
double const SIDE_STEP_COST = 1;
double const DIAGONAL_STEP_COST = 1.41421; // sqrt(2)

Coordinate const error_pos = {-1,-1};

bool equal_pos(Coordinate pos_one, Coordinate pos_two)
{
    return (pos_one.x == pos_two.x && pos_one.y == pos_two.y);
}

Node** create_nodes(bool *create_error)
{
    height_of_node = SCREEN_HEIGHT/ZOMBIE_PRECISION;
    width_of_node = SCREEN_WIDTH/ZOMBIE_PRECISION;
    Node **new_nodes = (Node**) malloc(sizeof(Node*) * height_of_node);
    if(new_nodes == NULL) {
        printf("Error: Couldn't allocate memory for **new_nodes in create_nodes!\n");
        *create_error = true;
        return NULL;
    } else {
        for(int i=0;i<height_of_node;i++) {
            new_nodes[i] = (Node*) malloc(sizeof(Node) * width_of_node);
            if(new_nodes[i] == NULL) {
                printf("Error: Couldn't allocate memory for new_nodes[%d] in create_nodes!\n",i);
                *create_error = true;
            }
        }
        return new_nodes;
    }
}

void setup_nodes(Node **nodes)
{
    for(int i=0;i<height_of_node;i++) {
        for(int j=0;j<width_of_node;j++) {
            nodes[i][j].pos.x = i;
            nodes[i][j].pos.y = j;
            nodes[i][j].in_closed_set = false;
            nodes[i][j].in_open_set = false;
            nodes[i][j].walkable = true;
            nodes[i][j].g_cost = DBL_MAX;
            nodes[i][j].f_cost = DBL_MAX;
        }
    }
}

UnitID get_closest_player(Entity *zombie, Entity *player1, Entity *player2)
{
    double distance1 = distance(zombie->pos,player1->pos);
    double distance2;
    if(player_two_active)
        distance2 = distance(zombie->pos,player2->pos);
    else
        distance2 = DBL_MAX;
    return distance1 < distance2 ? uPLAYER_ONE : uPLAYER_TWO;
}

int get_distance(Coordinate pos, Entity *player)
{
    return (int)round(sqrt(pow(pos.x - player->pos.x/ZOMBIE_PRECISION,2)+pow(pos.y - player->pos.y/ZOMBIE_PRECISION,2)));
}

Coordinate closest_node_position(Entity *player)
{
    int min = INT_MAX;
    Coordinate min_pos = error_pos;
    int distance;
    for(int i=0;i<height_of_node;i++) {
        for(int j=0;j<height_of_node;j++) {
            distance = get_distance((Coordinate){i,j},player);
            if(distance < min) {
                min = distance;
                min_pos.x = i;
                min_pos.y = j;
            }
        }
    }
    if(equal_pos(min_pos,error_pos))
        printf("Error: Closest node position not found!\n");
    return min_pos;
}

Node** add_to_set(Node *set[], int *size, Node *plus_node)
{
    *size += 1;
    Node **new_set = (Node**) malloc(sizeof(Node*)*(*size));
    if(new_set != NULL) {
        for(int i=0;i<*size-1;i++) {
            new_set[i] = set[i];
        }
        new_set[*size-1] = plus_node;
        new_set[*size-1]->in_open_set = true;
        free(set);
        return new_set;
    } else {
        printf("Error: Couldn't allocate memory for new_set in add_to_set!\n");
        free(set);
        return NULL;
    }
}

Node** remove_from_set(Node *set[], int *size, Coordinate node_pos)
{
    *size -= 1;
    Node **new_set = (Node**) malloc(sizeof(Node*)*(*size));
    if(new_set != NULL)  {
        for(int i=0,j=0;i<*size+1;i++) {
            if(!equal_pos(set[i]->pos,node_pos)) {
                new_set[j] = set[i];
                j++;
            }
        }
        free(set);
        return new_set;
    } else {
        printf("Error: Couldn't allocate memory for **new_set in remove_from set!\n");
        free(set);
        return NULL;
    }
}

double get_path_length(Coordinate from_pos, Coordinate to_pos)
{
    int x_difference = (int)fabs(to_pos.x-from_pos.x);
    int y_difference = (int)fabs(to_pos.y-from_pos.y);
    double diagonal_step_sum, side_step_sum;
    if(x_difference > y_difference) {
        diagonal_step_sum = y_difference*DIAGONAL_STEP_COST;
        side_step_sum = (x_difference-y_difference)*SIDE_STEP_COST;
    } else if(y_difference > x_difference) {
        diagonal_step_sum = x_difference*DIAGONAL_STEP_COST;
        side_step_sum = (y_difference-x_difference)*SIDE_STEP_COST;
    } else {
        diagonal_step_sum = x_difference*DIAGONAL_STEP_COST;
        side_step_sum = 0;
    }
    return (diagonal_step_sum+side_step_sum);
}

bool in_bounds(int i, int j, Coordinate start_pos)
{
    bool x_okay = (start_pos.x+i >= 0 && start_pos.x+i < width_of_node);
    bool y_okay = (start_pos.y+j >= 0 && start_pos.y+j < height_of_node);
    return (x_okay && y_okay);
}

Node* lowest_f_cost(Node *open_set[], int size)
{
    double lowest = open_set[0]->f_cost;
    int lowest_node_index = -1;
    for(int i=0;i<size;i++) {
        if(open_set[i]->f_cost <= lowest){
            lowest = open_set[i]->f_cost;
            lowest_node_index = i;
        }
    }
    if(lowest_node_index == -1)
        printf("Error in lowest_f_cost! Lowest_node_index not found!\n");
    return open_set[lowest_node_index];
}

Coordinate get_next_pos(Node **nodes, Coordinate current_node_pos)
{
    Coordinate prev_pos = error_pos;
    Coordinate prev_prev_pos = error_pos;
    while(!equal_pos(current_node_pos,error_pos)) {
        prev_prev_pos = prev_pos;
        prev_pos = current_node_pos;
        current_node_pos = nodes[(int)current_node_pos.x][(int)current_node_pos.y].parent;
    }
    if(equal_pos(prev_prev_pos,error_pos))
        printf("Error in get_next_pos! prev_pos not found!\n");
    return prev_prev_pos;
}

Coordinate a_star_search(Node **nodes, Coordinate start_pos, Coordinate goal_pos)
{
    nodes[(int)start_pos.x][(int)start_pos.y].g_cost = 0;
    nodes[(int)start_pos.x][(int)start_pos.y].parent = error_pos;

    Node **open_set = NULL;
    int open_set_size = 0;
    open_set = add_to_set(open_set,&open_set_size,&nodes[(int)start_pos.x][(int)start_pos.y]);
    if(open_set == NULL)
        return start_pos;

    Node *current_node;

    while(open_set_size > 0) {
        current_node = lowest_f_cost(open_set,open_set_size);
        if(equal_pos(current_node->pos,goal_pos)) {
            free(open_set);
            return get_next_pos(nodes,current_node->pos);
        }

        current_node->in_closed_set = true;
        open_set = remove_from_set(open_set,&open_set_size,current_node->pos);
        if(open_set == NULL)
            return start_pos;

        for(int i=-1;i<2;i++) {
            for(int j=-1;j<2;j++) {
                if(in_bounds(i,j,start_pos)) {
                    Node *neighbour_node = &nodes[(int)current_node->pos.x+i][(int)current_node->pos.y+j];
                    if(!neighbour_node->in_closed_set) {
                        double new_g_cost = current_node->g_cost + get_path_length(current_node->pos,neighbour_node->pos);

                        if(!neighbour_node->in_open_set) {
                            open_set = add_to_set(open_set,&open_set_size,neighbour_node);
                            if(open_set == NULL)
                                return start_pos;
                        } else if(new_g_cost >= neighbour_node->g_cost) {
                            continue;
                        }

                        neighbour_node->parent = current_node->pos;
                        neighbour_node->g_cost = new_g_cost;
                        neighbour_node->f_cost = neighbour_node->g_cost + get_path_length(neighbour_node->pos,goal_pos);
                    }
                }
            }
        }
    }
    printf("Error: Next position not found in a_star_search!\n");
    return start_pos;
}

void free_nodes(Node **nodes)
{
    for(int i=0;i<height_of_node;i++) {
        if(nodes[i] != NULL)
            free(nodes[i]);
    }
    free(nodes);
}

void find_path(Entity *zombie, Entity *player1, Entity *player2)
{
    bool create_error = false;
    Node **nodes = create_nodes(&create_error);
    if(nodes != NULL && !create_error) {
        setup_nodes(nodes);
        Coordinate start_pos = {(int)round(zombie->pos.x/ZOMBIE_PRECISION), (int)round(zombie->pos.y/ZOMBIE_PRECISION)};
        UnitID closest_player = get_closest_player(zombie,player1,player2);
        Coordinate goal_pos;
        if(closest_player == uPLAYER_ONE)
            goal_pos = closest_node_position(player1);
        else
            goal_pos = closest_node_position(player2);
        if(!equal_pos(start_pos,goal_pos)) {
            Coordinate next_node_pos = a_star_search(nodes, start_pos, goal_pos);
            zombie->next_pos.x = next_node_pos.x*ZOMBIE_PRECISION;
            zombie->next_pos.y = next_node_pos.y*ZOMBIE_PRECISION;
        }
    } else {
        printf("Error: Couldn't find zombie path!\n");
    }
    free_nodes(nodes);
}