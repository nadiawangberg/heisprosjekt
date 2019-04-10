#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "door.h"
#include "elev.h"
#include "order.h"
#include "emergencystop.h"
#include "floor.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
* @file
* @brief Finite state machine, switches between the 4 states IDLE, RUNNING, DOOR_OPEN, EMERGENCYSTOP
*/

static elev_motor_direction_t motor_dir_m = DIRN_STOP;

static Floor meas_floor_m = UNDEFINED;
static Floor floor_m = UNDEFINED;
static float position_m = -1;

typedef enum tag_state {
	IDLE = 1,
	RUNNING,
	DOOR_OPEN,
	EMERGENCYSTOP
} State;

static State curr_state_m; // Global state variable
static State prev_state_m;


void init_FSM();

void FSM();

void PrintState_FSM(State state);

#endif // #ifndef __INCLUDE_FSM_H__
