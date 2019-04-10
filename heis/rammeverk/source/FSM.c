#include "FSM.h"


void PrintState(State state) {

	switch(state) {
		case INIT:
			printf("Init state");
			break;
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

void StateMachineInit() {
	elev_set_motor_direction(DIRN_DOWN);

	//find floor
	do{
		in_between_floor=elev_get_floor_sensor_signal();
	} while(in_between_floor==UNDEFINED);
	
	elev_set_floor_indicator(in_between_floor); //set light
	elev_set_motor_direction(DIRN_STOP);

    curr_state = IDLE;
    motor_dir_g = DIRN_STOP;
}

void StateMachine() {
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
			curr_state=EMERGENCYSTOP;
		}
		switch(curr_state) {

			case INIT:
				break;

			case IDLE: // test
				//printf("                    in_between_floor: %.6f                   \n",in_between_floor);
				
				motor_dir_g=selectDir_order(in_between_floor,DIRN_STOP);
				//printf("%i\n",motor_dir_g );
			 	//printf("%i",motor_dir_g);
				if(motor_dir_g!=DIRN_STOP){ // motor_dir = UP / DOWN
					curr_state=RUNNING;
					//printf("                    in_between_floor: %.6f                   \n",in_between_floor);
					//printf("%i",motor_dir_g);
					elev_set_motor_direction(motor_dir_g);

				}
				else if(motor_dir_g==DIRN_STOP && !orderListsEmpty_order()){ // if there are any orders
					curr_state=DOOR_OPEN;

				}
				prev_state = IDLE;
				break;

			case RUNNING:

				if (in_between_floor==(int)in_between_floor ) {
					in_between_floor=last_floor+0.5*motor_dir_g;
				}
				
				if (curr_floor != UNDEFINED && shouldLiftStop_order(last_floor,motor_dir_g)) { // stop when you reach a floor with appropriate order, shouldLiftStop(last_floor, motor_dir_g)		
        			curr_state = DOOR_OPEN;
        			prev_state = RUNNING;
        			break;
    			}
				prev_state = RUNNING;
				break;

			case DOOR_OPEN:
				//removeOrders(last_floor);
				if (prev_state != curr_state || isOrderInFloor_order(last_floor)) { // just transitioned to door open
					in_between_floor=last_floor;
					//removeOrders(last_floor);
					init_door(); // timer started
				}
				removeOrders_order(last_floor);
				if (timerDone_door()) {
					elev_set_door_open_lamp(0);
					motor_dir_g = selectDir_order(last_floor, motor_dir_g);
					//in_between_floor=last_floor+0.5*motor_dir_g;
					elev_set_motor_direction(motor_dir_g);
					if(motor_dir_g!=DIRN_STOP){
						curr_state = RUNNING;
					}
					else{
						curr_state=IDLE;
					}
					prev_state = DOOR_OPEN;
					break;
				}

				prev_state = DOOR_OPEN;
				break;

			case EMERGENCYSTOP:
				if(curr_floor!=UNDEFINED){ //hvis vi er i en etasje
					elev_set_door_open_lamp(1);
				}
				init_emergencystop();
				if(prev_state)
				while(elev_get_stop_signal());
				elev_set_stop_lamp(0);
				if (curr_floor!=UNDEFINED){
					curr_state=DOOR_OPEN;
				}
				else{
					curr_state=IDLE;
				}
				prev_state=EMERGENCYSTOP;
				break;
		}
	}
}