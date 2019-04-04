
#include "door.h"

#include "elev.h"
#include <stdio.h>
#include <unistd.h>

//static int msec = 0, trigger = 3000; // 3sec??

void DoorStateInit() {
	//msec = 0;
	//trigger = 3000;
	//printf("In door open (initializing phase)!");
	//printf("In door open func, lights, motor off \n");
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	StartTimer();
}


void DoorStateExit() {
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