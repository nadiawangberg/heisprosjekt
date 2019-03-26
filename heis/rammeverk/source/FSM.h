#include "door.h"


typedef enum tag_state {
	INIT = 0,
	IDLE,
	RUNNING,
	DOOR_OPEN,
	STOP 
} State;


void StateMachine() {
	while(1) {
		// gjør generelle ting unless visse krav
		switch(state) {
			case IDLE:
				// noe
				break;
			case RUNNING:
				printf("In running state, nothing here atm");
				// noe
				break;
			case DOOR_OPEN:
				printf("In door open state, will run door open func\n");
				DoorOpen();
				break;
			case STOP:
				// noe
				break;
		}
	}
}