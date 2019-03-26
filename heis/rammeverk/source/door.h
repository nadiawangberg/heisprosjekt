#include "elev.h"

void DoorOpen() {
	printf("In door open func, lights, motor off \n");
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	// funk kalles så lenge vi er i state
}