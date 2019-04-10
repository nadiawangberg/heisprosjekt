
#ifndef __INCLUDE_DOOR_H__
#define __INCLUDE_DOOR_H__

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "elev.h"
#include "liftMovement.h"
#include "order.h"


static int msec = 0;
static int trigger = 3000;
static clock_t difference, before;

/**
Initializes door state.
Stops lift, sets door open light and starts 3sek door open timer.
*/
void init_door();

/**
Checks if timer is done for door open state, meaning that 3sek has passed.
@return 0 if timer isnt done. 1 if timer is done.
*/
int timerDone_door();


#endif // #ifndef __INCLUDE_DOOR_H__
