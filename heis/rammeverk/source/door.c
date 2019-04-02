
#include "door.h"

#include "elev.h"
#include <stdio.h>
#include <unistd.h>


void DoorInit() {
	printf("In door open!");
	//printf("In door open func, lights, motor off \n");
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	StartTimer();
}

void ResetTimer() {

}

void StartTimer() {

}

int TimerDone() {
	//return (msec > 3000);
	return 1;
}