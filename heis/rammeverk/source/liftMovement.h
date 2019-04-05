#ifndef __INCLUDE_LIFTMOVEMENT_H__
#define __INCLUDE_LIFTMOVEMENT_H__

#include "elev.h"
#include <stdio.h>

typedef enum tag_floor {
	UNDEFINED = -1,
	FIRST = 0,
	SECOND,
	THIRD,
	FOURTH 
} Floor;

static Floor floor = UNDEFINED;
//Floor last_floor = UNDEFINED;

/**
  O1, O2, O3
  Moves lift up until it reaches a floor. Sets current_floor.
*/
void positionInit();


/**
  Moves lift up unless ??
*/
//void up();


/**
  Moves lift down
*/
//void down();
#endif