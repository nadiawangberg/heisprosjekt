#include "FSM.h"

/*
typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	STOP 
} State;
*/

void PrintState(State state) {

	switch(state) {
		case INIT:
			printf("Init state");
			break;
		case IDLE:
			printf("Idle state");
			break;
		case RUNNING:
			printf("Running state");
			break;
		case DOOR_OPEN:
			printf("DoorOpen state");
			break;
		case STOP:
			printf("EmergencyStop state");		
			break;
		return;
	}
}

void StateMachineInit() {
    elev_set_motor_direction(DIRN_UP); // kjører opp
    curr_state = RUNNING;

}

void StateMachine() {

	StateMachineInit();

	while(1) {
		// PrintState(state);

		// gjør generelle ting unless visse krav
		switch(curr_state) {
			case INIT:
				//printf("In INIT state, nothing here atm\n");
				//noe
				break;
			case IDLE:
				// noe
				break;
			case RUNNING:
				if (elev_get_floor_sensor_signal() == 2) { // third floor
        			curr_state = DOOR_OPEN;
        			break;
    			}

				elev_set_motor_direction(DIRN_UP);
				elev_set_stop_lamp(1); // for debugging
				break;
			case DOOR_OPEN:
				if (prev_state != curr_state) {
					DoorInit(); // timer started
					prev_state = DOOR_OPEN;
				}

				if (TimerDone()) {
					curr_state = RUNNING;
					ResetTimer();
				}
				// PrintState(curr_state);
				break;
			case STOP:
				// noe
				break;
		}
	}
}