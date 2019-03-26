#include "door.h"


typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	STOP 
} State;


void StateMachine(State state) {
	int open = 0;
	while(1) {
		printf("State: %d\n", state);
		// TEST
    	if (elev_get_floor_sensor_signal() == 2) {
        	state = DOOR_OPEN;
        	// start timer
    		}

		// gjør generelle ting unless visse krav
		switch(state) {
			case INIT:
				printf("In INIT state, nothing here atm\n");
				//noe
				break;
			case IDLE:
				// noe
				break;
			case RUNNING:
				// just for debugging xDD
				printf("IN RUNNING STATE");
				elev_set_stop_lamp(1);
				break;
			case DOOR_OPEN:
				open = DoorOpen();
				if (open == 1) {
					state = RUNNING;
				}
				break;
			case STOP:
				// noe
				break;
		}
	}
}