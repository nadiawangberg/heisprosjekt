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
		position_m=elev_get_floor_sensor_signal();
	} while(position_m==UNDEFINED);
	
	elev_set_floor_indicator(position_m); //set light
	elev_set_motor_direction(DIRN_STOP);

    curr_state_m = IDLE;
    motor_dir_m = DIRN_STOP;
}


void FSM() {

	while(1) {

		checkForOrders_order(); // checks if any buttons pressed, adds to order list
		meas_floor_m = elev_get_floor_sensor_signal();
		
		if (meas_floor_m != UNDEFINED) { // we're in a floor
			elev_set_floor_indicator(meas_floor_m);
			floor_m = meas_floor_m;
			position_m = meas_floor_m;
		}

		//print_order();

		if(elev_get_stop_signal()){
			curr_state_m=EMERGENCYSTOP;
		}
		switch(curr_state_m) {
			case IDLE:				
				motor_dir_m=selectDir_order(position_m,DIRN_STOP);
				if(motor_dir_m!=DIRN_STOP){ // motor_dir = UP / DOWN
					curr_state_m=RUNNING;
					elev_set_motor_direction(motor_dir_m);

				}
				else if(motor_dir_m==DIRN_STOP && !areOrderListsEmpty_order()){ // if there are any orders
					curr_state_m=DOOR_OPEN;

				}
				prev_state_m = IDLE;
				break;

			case RUNNING:
				// position_m==(int)position_m
				if (meas_floor_m != UNDEFINED) { // if we're in a floor
					position_m=floor_m+0.5*motor_dir_m; // since we're going past a floor, update position
				}
				
				if (meas_floor_m != UNDEFINED && shouldLiftStop_order(floor_m,motor_dir_m)) { // stop when you reach a floor with appropriate order	
        			curr_state_m = DOOR_OPEN;
        			prev_state_m = RUNNING;
        			break;
    			}
				prev_state_m = RUNNING;
				break;

			case DOOR_OPEN:
				if (prev_state_m != curr_state_m || isOrderInFloor_order(floor_m)) { // if lift just transitioned to door_open and there are orders
					position_m=floor_m;
					init_door(); // timer started
				}
				removeOrders_order(floor_m);

				if (timerDone_door()) {
					elev_set_door_open_lamp(0);
					motor_dir_m = selectDir_order(floor_m, motor_dir_m);
					elev_set_motor_direction(motor_dir_m);
					if(motor_dir_m!=DIRN_STOP){
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
				if(meas_floor_m!=UNDEFINED){ //hvis vi er i en etasje
					elev_set_door_open_lamp(1);
				}
				init_emergencystop();
				while(elev_get_stop_signal());
				elev_set_stop_lamp(0);
				if (meas_floor_m!=UNDEFINED){
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