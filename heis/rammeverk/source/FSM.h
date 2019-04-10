#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "door.h"
#include "elev.h"
#include "order.h"
#include "stop.h"
#include "floor.h"
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

/*
typedef enum tag_floor {
	UNDEFINED = -1,
	FIRST = 0,
	SECOND = 1,
	THIRD = 2,
	FOURTH = 3 
} Floor;

static Floor floor = UNDEFINED;
static Floor floor_TEST = UNDEFINED;
*/

// global variables
static elev_motor_direction_t motor_dir_g = DIRN_STOP; // will ONLY be DIRN_STOP for idle and emergency stop state, will remain its direction  for door open state
//static order_direction_t order_dir = DOWN;
static Floor curr_floor = UNDEFINED;
static Floor last_floor = UNDEFINED;
static float in_between_floor = -1;

typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	EMERGENCYSTOP
} State;

static State curr_state = INIT; // Global state variable
static State prev_state = INIT;


void StateMachineInit();

void StateMachine();

void PrintState(State state);

#endif // #ifndef __INCLUDE_FSM_H__
