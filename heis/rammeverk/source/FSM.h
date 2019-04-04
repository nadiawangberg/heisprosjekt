#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__


typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	STOP 
} State;

static State state= INIT;
void StateMachine() {
	while(1) {
		// gjør generelle ting unless visse krav

		orderManager(); // changing state

		switch(state) {
			case IDLE:

				// noe
				break;
			case RUNNING:
				// move in cur direction
				// elev_set_motor_direction

				// if feeling somthing --> state = door_open
						// break;
				// noe


				// If prev state != running
					// transition / init behavior
				break;
			case DOOR_OPEN:
				// chillern
				// removeOrder (rememeber to only do it once, needs to be in transition func)
				break;
			case STOP:
				// noe
				// normal stop behavior
				break;
		}
	}
}
#endif 