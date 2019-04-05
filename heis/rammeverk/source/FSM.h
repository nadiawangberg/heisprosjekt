#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__

#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "door.h"
#include "elev.h"
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	STOP 
} State;


static State curr_state = INIT; // Global state variable
static State prev_state = INIT;


void StateMachineInit();

void StateMachine();

void PrintState(State state);

void transitionFromDoorOpen();

#endif // #ifndef __INCLUDE_FSM_H__
