//
// Created by Patrick on 2018-10-23.
//

#include "Timer.h"
#include "Globals.h"

#define SCREEN_FPS 60;
int const SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

uint32_t startTick;
uint32_t endTick;
uint32_t currentTick;
uint32_t lastTick;
uint32_t timePassed;

void start_Timer()
{
    startTick = SDL_GetTicks();
    lastTick = startTick;
}

void calculate_timePassed()
{
    currentTick = SDL_GetTicks();
    timePassed = currentTick - lastTick;
}

uint32_t get_timeSinceStart()
{
    return currentTick - startTick;
}

uint32_t get_gameTickCount()
{
    return endTick - startTick;
}

uint32_t get_currentTick()
{
    return currentTick;
}

uint32_t get_timePassed()
{
    return timePassed;
}

void cap_frame_rate()
{
    if(timePassed < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - timePassed);
    }
}

void set_lastTick()
{
    lastTick = currentTick;
}

void end_Timer()
{
    endTick = currentTick;
}
