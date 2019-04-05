
#ifndef __INCLUDE_DOOR_H__
#define __INCLUDE_DOOR_H__

#include <time.h>

//clock_t before = clock();
//clock_t difference = clock() - before;
//clock_t before = 0; 
//clock_t difference = 0;
//int msec = 0;


static int msec = 0;
static int trigger = 3000;
static clock_t difference, before;

void DoorStateInit();

void ResetTimer();

void StartTimer();

int TimerDone();

void DoorStateExit();

#endif // #ifndef __INCLUDE_DRIVER_H__
