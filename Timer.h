//
// Created by Patrick on 2018-10-23.
//

#ifndef ZOMBIE_SURVIVAL_TIME_H
#define ZOMBIE_SURVIVAL_TIME_H

#include <stdint.h>

void start_Timer();
void calculate_timePassed();
uint32_t get_timeSinceStart();
uint32_t get_gameTickCount();
uint32_t get_currentTick();
uint32_t get_timePassed();
void cap_frame_rate();
void set_lastTick();
void end_Timer();

#endif //ZOMBIE_SURVIVAL_TIME_H
