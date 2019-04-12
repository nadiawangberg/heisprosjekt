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
* @brief Finite state machine, switches between the 4 finite states @c IDLE, @c RUNNING, @c DOOR_OPEN, @c EMERGENCYSTOP
*/

static elev_motor_direction_t motor_dir_m = DIRN_STOP;

static Floor meas_floor_m = UNDEFINED;
static Floor floor_m = UNDEFINED;
static float position_m = -1;

/**
	The different states the FSM can be in. 
*/
typedef enum tag_state {
	IDLE = 1,
	RUNNING,
	DOOR_OPEN,
	EMERGENCYSTOP
} State;

static State curr_state_m;
static State prev_state_m;

/**
  @brief Initializes state machine
  Initializes lift positition, 
  when position is initialized lift transitions to idle state. 
*/
void init_FSM();


/**
  @brief Runs the finite state machine.
  There are 4 states, @c EMERGENCYSTOP, @c DOOR_OPEN, @c RUNNING and @c IDLE given by struct State. 
  Emergency stop state and door open state are described by their corresponding modules.
  Running state is moving the lift in the direction given by the order module. 
  In idle the lift is waiting for orders with the doors closed.
  The transitions between states is shown and explained in the state diagram.
*/
void FSM();

/**
  @brief Prints state
  @param @p state Which state to print
*/
void PrintState_FSM(State state);

#endif // #ifndef __INCLUDE_FSM_H__
