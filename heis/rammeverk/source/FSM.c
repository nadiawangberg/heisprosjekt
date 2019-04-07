#include "FSM.h"


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
	//positionInit();
    curr_state = RUNNING;
    printf("DONE WITH STATE MACHINE INIT!!");
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
	while(1) {
		// PrintState(state);

		// gjør generelle ting unless visse krav

		checkForOrders(); // checks if any buttons pressed, adds to order list

		curr_floor = elev_get_floor_sensor_signal(); // will be undefined most of the time
		if (curr_floor != UNDEFINED) { // we're in a floor
			motor_dir_g = selectDir(curr_floor, motor_dir_g);
			elev_set_floor_indicator(curr_floor);
			//removeOrders(curr_floor);
			last_floor = curr_floor;

		}

		//elev_set_floor_indicator(last_floor);
		printOrders();
		switch(curr_state) {
			case INIT:
				//printf("In INIT state, nothing here atm\n");
				//noe
				break;
			case IDLE:
				// noe
				prev_state = IDLE;
				break;
			case RUNNING:
				if (curr_floor != UNDEFINED && isOrderInFloor(curr_floor)) { // we're in a floor, stop     			
        			curr_state = DOOR_OPEN;
        			removeOrders(curr_floor);
        			elev_set_stop_lamp(0);

        			//motor_dir_g = DIRN_UP;
        			prev_state = RUNNING;
        			break;
    			}

				elev_set_motor_direction(motor_dir_g); // motor_dir_g, DIRN_UP
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