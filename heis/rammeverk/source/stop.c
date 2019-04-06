#include "stop.h"
void checkEmergencyStop{
	if(elev_get_stop_signal()){
		curr_state=EMERGENCYSTOP;
	}
}
void emergencyStopInit{
	elev_set_stop_lamp(1);
	motor_dir_g=DIRN_STOP;
	elev_set_motor_direction(motor_dir_g);
	removeAllOrders();
}

void emergencyStopExit(){
	elev_set_stop_lamp(0);
}