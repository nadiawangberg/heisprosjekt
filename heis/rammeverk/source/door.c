
#include "door.h"
#include <stdio.h>

void DoorStateInit() {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	StartTimer();
}


void DoorStateExit(Floor curr_floor,elev_motor_direction_t motor_dir_g) {
	elev_set_door_open_lamp(0);
	ResetTimer();
	//motor_dir_g = selectDir(curr_floor, motor_dir_g);
	printf( "%i\n", motor_dir_g );
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