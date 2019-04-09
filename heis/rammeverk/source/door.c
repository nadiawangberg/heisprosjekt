#include "door.h"

void init_door() {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_door_open_lamp(1);
	before_m = clock(); // start_timer_door
}

int timerDone_door() {
	difference_m = clock() - before_m;
  	msec_m = difference_m * 1000 / CLOCKS_PER_SEC;
  	return (msec_m >= trigger_m);
}