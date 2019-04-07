
#include "door.h"
#include <stdio.h>

void DoorStateInit() {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	StartTimer();
}


void DoorStateExit(Floor curr_floor) {
	elev_set_door_open_lamp(0);
	ResetTimer();
}

void ResetTimer() {

}

void StartTimer() {
	before = clock();
}

int TimerDone() {
	difference = clock() - before;
  	msec = difference * 1000 / CLOCKS_PER_SEC;
  	//printf("difference: %d \n", msec);
  	return (msec >= trigger); // returns 0 or 1
}