#include "FSM.h"


void PrintState_FSM(State state) {
	switch(state) {
		case IDLE:
			printf("Idle state");
			break;
		case RUNNING:
			printf("Running state");
			break;
		case DOOR_OPEN:
			printf("DoorOpen state");
			break;
		case EMERGENCYSTOP:
			printf("EmergencyStop state");		
			break;
		return;
	}
}


void init_FSM() {
	elev_set_motor_direction(DIRN_DOWN);
	//find floor
	do{
		in_between_floor=elev_get_floor_sensor_signal();
	} while(in_between_floor==UNDEFINED);
	
	elev_set_floor_indicator(in_between_floor); //set light
	elev_set_motor_direction(DIRN_STOP);

    curr_state_m = IDLE;
    motor_dir_g = DIRN_STOP;
}


void FSM() {
	
	while(1) {

		checkForOrders_order(); // checks if any buttons pressed, adds to order list
		curr_floor = elev_get_floor_sensor_signal();
		
		if (curr_floor != UNDEFINED) { // we're in a floor
			elev_set_floor_indicator(curr_floor);
			last_floor = curr_floor;
			in_between_floor = curr_floor;
		}

		elev_set_floor_indicator(last_floor);
		print_order();

		if(elev_get_stop_signal()){
			curr_state_m=EMERGENCYSTOP;
		}
		switch(curr_state_m) {
			case IDLE:				
				motor_dir_g=selectDir_order(in_between_floor,DIRN_STOP);
				if(motor_dir_g!=DIRN_STOP){ // motor_dir = UP / DOWN
					curr_state_m=RUNNING;
					elev_set_motor_direction(motor_dir_g);

				}
				else if(motor_dir_g==DIRN_STOP && !orderListsEmpty_order()){ // if there are any orders
					curr_state_m=DOOR_OPEN;

				}
				prev_state_m = IDLE;
				break;

			case RUNNING:

				if (in_between_floor==(int)in_between_floor ) {
					in_between_floor=last_floor+0.5*motor_dir_g;
				}
				
				if (curr_floor != UNDEFINED && shouldLiftStop_order(last_floor,motor_dir_g)) { // stop when you reach a floor with appropriate order, shouldLiftStop(last_floor, motor_dir_g)		
        			curr_state_m = DOOR_OPEN;
        			prev_state_m = RUNNING;
        			break;
    			}
				prev_state_m = RUNNING;
				break;

			case DOOR_OPEN:

				if (prev_state_m != curr_state_m || isOrderInFloor_order(last_floor)) { // just transitioned to door open
					in_between_floor=last_floor;
					init_door(); // timer started
				}
				removeOrders_order(last_floor);

				if (timerDone_door()) {
					elev_set_door_open_lamp(0);
					motor_dir_g = selectDir_order(last_floor, motor_dir_g);
					elev_set_motor_direction(motor_dir_g);
					if(motor_dir_g!=DIRN_STOP){
						curr_state_m = RUNNING;
					}
					else{
						curr_state_m=IDLE;
					}
					prev_state_m = DOOR_OPEN;
					break;
				}

				prev_state_m = DOOR_OPEN;
				break;

			case EMERGENCYSTOP:
				if(curr_floor!=UNDEFINED){ //hvis vi er i en etasje
					elev_set_door_open_lamp(1);
				}
				init_emergencystop();
				if(prev_state_m)
				while(elev_get_stop_signal());
				elev_set_stop_lamp(0);
				if (curr_floor!=UNDEFINED){
					curr_state_m=DOOR_OPEN;
				}
				else{
					curr_state_m=IDLE;
				}
				prev_state_m=EMERGENCYSTOP;
				break;
		}
	}
}