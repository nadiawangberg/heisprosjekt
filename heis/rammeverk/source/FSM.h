#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "elev.h"
#include "door.h"
#include "order.h"
#include "emergencystop.h"
#include "liftMovement.h"
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

// global variables
static elev_motor_direction_t motor_dir_g = DIRN_STOP; // will ONLY be DIRN_STOP for idle and emergency stop state, will remain its direction  for door open state
//static order_direction_t order_dir = DOWN;
static Floor curr_floor = UNDEFINED;
static Floor last_floor = UNDEFINED;
static float in_between_floor = -1;


/**
	The different states the FSM can be in. 
*/
typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	EMERGENCYSTOP
} State;


static State curr_state = INIT; // Global state variable
static State prev_state = INIT;

/**
  Initializes state machine
  Initializes lift positition, 
  when position is initialized lift transitions to idle state. 
*/
void StateMachineInit();


/**
  Runs the finite state machine.
  There are 4 states, EMERGENCYSTOP, DOOR_OPEN, RUNNING and IDLE given by struct State. 
  Emergency stop state and door open state are described by their corresponding modules.
  Running state is moving the lift in the direction given by the order module. 
  In idle the lift is waiting for orders with the doors closed.
  The transitions between states is shown and explained in the state diagram.
*/
void StateMachine();

/**
  Prints state
  @param state Which state to print
*/
void PrintState(State state);

#endif // #ifndef __INCLUDE_FSM_H__
