#ifndef __INCLUDE_LIFTMOVEMENT_H__
#define __INCLUDE_LIFTMOVEMENT_H__

#include "elev.h"
#include <stdio.h>

/**
* @file
* @brief floor module, containing the floor enum. 
*/


/**
  Enum with the discrete floors of the lift, @c UNDEFINED, @c FIRST, @c SECOND, @c THIRD, @c FOURTH
*/
typedef enum tag_floor {
	UNDEFINED = -1,
	FIRST = 0,
	SECOND = 1,
	THIRD = 2,
	FOURTH = 3 
} Floor;


#endif