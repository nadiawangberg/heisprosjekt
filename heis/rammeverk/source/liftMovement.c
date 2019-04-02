#include "liftMovement.h"
#include "elev.h"



void positionInit(){
	elev_set_motor_direction(DIRN_UP);
	//find floor
	do{
		current_floor=elev_get_floor_sensor_signal();
	} while(current_floor==UNDEFINED);
	
	last_floor=current_floor; 
	elev_set_floor_indicator(current_floor); //set light
	elev_set_motor_direction(DIRN_STOP);
}


/*void up(){

}

void down(){

}*/