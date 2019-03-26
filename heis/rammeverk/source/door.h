#include "elev.h"
#include <stdio.h>
#include <unistd.h>

int DoorOpen() {
	//printf("In door open func, lights, motor off \n");
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	// funk kalles så lenge vi er i state

	sleep(3); // NEEDS TO BE REPLACED BY A TIMER THAT LOOPS THROUGH STATE MACHINE

	return 1;
}