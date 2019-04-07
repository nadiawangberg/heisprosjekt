#include "liftMovement.h"

void positionInit(){
	elev_set_motor_direction(DIRN_DOWN);
	//find floor
	do{
		floor=elev_get_floor_sensor_signal();
	} while(floor==UNDEFINED);
	
	//last_floor=current_floor; 
	elev_set_floor_indicator(floor); //set light
	elev_set_motor_direction(DIRN_STOP);
	printf("DONE WITH INIT, BYE!");
}


/*void up(){

}

void down(){

}*/