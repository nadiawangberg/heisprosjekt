#include "liftMovement.h"




void positionInit(){
elev_set_motor_direction(DIRN_UP);
do{
	floor=elev_get_floor_sensor_signal();
} while(floor==undefined);
elev_set_floor_indicator(floor);
elev_set_motor_direction(DIRN_STOP);
}

void up(){

}

void down(){

}