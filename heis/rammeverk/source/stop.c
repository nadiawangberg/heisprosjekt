#include "stop.h"

void emergencyStopInit(){
	elev_set_stop_lamp(1);
	motor_dir_g=DIRN_STOP;
	elev_set_motor_direction(motor_dir_g);
	removeAllOrders();
}

void emergencyStopExit(){
	elev_set_stop_lamp(0);
}