#include "door.h"
#include <stdio.h>

void init_door() {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	before = clock(); // StartTimer();
}

int timerDone_door() {
	difference = clock() - before;
  	msec = difference * 1000 / CLOCKS_PER_SEC;
  	return (msec >= trigger);
}