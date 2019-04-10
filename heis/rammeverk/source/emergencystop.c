#include "emergencystop.h"

void init_emergencystop(){
	elev_set_stop_lamp(1);
	motor_dir_m=DIRN_STOP;
	elev_set_motor_direction(motor_dir_m);
	removeAllOrders_order();
}