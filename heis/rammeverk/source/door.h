#ifndef __INCLUDE_DOOR_H__
#define __INCLUDE_DOOR_H__

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "elev.h"


static int msec = 0;
static int trigger = 3000;
static clock_t difference, before;

/**
* @file
* @brief door module, handles door open functionality, 
  ensures the door is opened for 3 seconds then closed again when taking an order.
*/


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
