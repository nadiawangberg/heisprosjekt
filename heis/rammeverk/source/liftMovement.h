#ifndef __INCLUDE_LIFTMOVEMENT_H__
#define __INCLUDE_LIFTMOVEMENT_H__

#include "elev.h"
#include <stdio.h>


/**
  Enum with the discrete floors of the lift
*/
typedef enum tag_floor {
	UNDEFINED = -1,
	FIRST = 0,
	SECOND = 1,
	THIRD = 2,
	FOURTH = 3 
} Floor;

static Floor floor = UNDEFINED;
//Floor last_floor = UNDEFINED;

/**
  Moves lift down until it reaches a floor.
*/
Floor positionInit();


/**
  Moves lift up unless ??
*/
//void up();


/**
  Moves lift down
*/
//void down();
#endif