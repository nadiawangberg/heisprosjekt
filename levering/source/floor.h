#ifndef __INCLUDE_LIFTMOVEMENT_H__
#define __INCLUDE_LIFTMOVEMENT_H__

#include "elev.h"
#include <stdio.h>

/**
  @brief Enum with the discrete floors of the lift
*/
typedef enum tag_floor {
	UNDEFINED = -1,
	FIRST = 0,
	SECOND = 1,
	THIRD = 2,
	FOURTH = 3 
} Floor;


#endif