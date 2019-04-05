#include "FSM.h"
#include "liftMovement.h"

int been_in_2nd_floor = 0;

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
	// for testing for now
	positionInit();
    elev_set_motor_direction(DIRN_UP); // kjører opp
    curr_state = RUNNING;

    //elev_set_motor_direction(DIRN_STOP); // kjører opp
    //curr_state = IDLE;

}

void transitionFromDoorOpen() {
	// ALL STATE TRANSITIONS FROM DOOR OPEN
	curr_state = RUNNING;
	prev_state = DOOR_OPEN;

	/* prepartion for more states
	if (prev_state == EMERGENCYSTOP)
		curr_state = EMERGENCYSTOP;
	else if (order_direction_g == DIRN_UP || order_direction_g == DIRN_DOWN) :
		curr_state = RUNNING;
		elev_set_door_open_lamp(0); // close doors 
	else if (no orders) {
		elev_set_door_open_lamp(0); // close doors 
		curr_state = IDLE;
		}

	else if (no orders)
	*/
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
				if (elev_get_floor_sensor_signal() == 2 && !been_in_2nd_floor) { // third floor
        			
        			curr_state = DOOR_OPEN;
        			elev_set_stop_lamp(0);

        			prev_state = RUNNING;
        			been_in_2nd_floor = 1;
        			break;
    			}

				elev_set_motor_direction(DIRN_UP);
				elev_set_stop_lamp(1); // for debugging (REMEMBER TO REMOVE)
				
				prev_state = RUNNING;
				break;
			case DOOR_OPEN:
				if (prev_state != curr_state) { // just transitioned to door open
					DoorStateInit(); // timer started
				}

				if (TimerDone()) {
					curr_state = RUNNING;
					// transitionFromDoorOpen();
					DoorStateExit();
					break;
				}

				prev_state = DOOR_OPEN; // is it an issue to set prev_state = curr_state before EVERY break?
				break;
			case STOP:
				// noe
				break;
		}
	}
}