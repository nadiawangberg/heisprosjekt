
#include "elev.h"
#include "order.h"
#include "FSM.h"
#include <stdio.h>

void printOrders(){
	printf("order_priority_up: ");
	for (int i=0;i<4;i+=1){
			printf("%d ",order_priority_up[i]);
	}
	printf("\n order_priority_down: ");
	for (int i=0;i<4;i+=1){
			printf("%d ",order_priority_down[i]);
	}
}



void addOrder(Floor floor, order_direction_t order_dir){
	if(order_dir==UP){ // person wanting to go up
		order_priority_up[floor]=1;
		elev_set_button_lamp(BUTTON_CALL_UP,floor, 1);	
	}
	else if(order_dir==DOWN){
		order_priority_down[floor]=1;
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 1);
	}
	else if (order_dir==COMMAND){ // aka person in lift pressed button (1-4) 
		elev_set_button_lamp(BUTTON_COMMAND,floor, 1);
		/*
		if(motor_dir_g==DIRN_UP){
			order_priority_up[floor]=1;
		}
		else if (motor_dir_g==DIRN_DOWN){ // Dir = down
			order_priority_down[floor]=1;
		}
		else if (motor_dir_g==DIRN_STOP)
			order_priority_up[floor]=1; // NOOOOOOOOO FIIIIIIIIIIIIIXXXX!!!!
		}
		*/
	}
}	


// removes all orders given a floor
void removeOrders(Floor floor){
	order_priority_up[floor]=0;
	order_priority_down[floor]=0;

	if (floor != FOURTH) {
		elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
	}

	if (floor != FIRST) {
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 0);
	}

	elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
	/* 
	if(order_priority_up[floor]==1){
		order_priority_up[floor]=0;
		elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
		if(order_priority_down[floor]==1){
			order_priority_down[floor]=0;
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 0);}
	}
	*/
	/* 
	if(motor_dir_g==DIRN_UP){
		if(order_priority_up[floor]==1)
			order_priority_up[floor]=0;
			elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
	}
	else if(order_priority_down[floor]==1){
		order_priority_down[floor]=0;
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 0);
	} 
	elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
	*/
}


void checkForOrders(){//feels if we have orders (button press), adds them to queue if there are orders (+lights)   //tested
	for(int i=0;i<4;i+=1){
		if(i!=3 && elev_get_button_signal(BUTTON_CALL_UP,i)){ // this results in elev_get_button_signal(BUTTON_CALL_UP,3) never being called
			addOrder(i,UP);
		}
		if(elev_get_button_signal(BUTTON_COMMAND,i)){
			addOrder(i,COMMAND);
		}
		if(i!=0 && elev_get_button_signal(BUTTON_CALL_DOWN,i)){ // this results in elev_get_button_signal(BUTTON_CALL_DOWN,0) never being called
			addOrder(i,DOWN);
		}
	}
}


elev_motor_direction_t selectDir(Floor floor, elev_motor_direction_t current_direction) { //Add edge case. Add case where pick up order under elev going up.
	// if (more orders in the current direction) 
	if(floor==FOURTH){
		return DIRN_DOWN;
	}
	else if(floor==FIRST){
		return DIRN_UP;
	}
	else if (current_direction==DIRN_UP){
		for(int i=floor+1;i<=3;i+=1){
			if(order_priority_up[i]){
				return DIRN_UP;
			}
		}
		for(int i=floor-1;i>=0;i-=1){
			if(order_priority_down[i]){
				return DIRN_DOWN;
			}
		}
	}
	else if(current_direction==DIRN_DOWN){
		for(int i=floor-1;i>=0;i-=1){
			if(order_priority_down[i]){
				return DIRN_DOWN;
			}
		}
		for(int i=floor+1;i<=3;i+=1){
			if(order_priority_up[i]){
				return DIRN_UP;
			}
		}
	}
	else if (current_direction == DIRN_STOP && !orderListsEmpty()) {
		//gjøre noe for å begynne å kjøre igjen, feks hvis lista ikke er tom

		return DIRN_UP; // NOOOOOOOOOOO, FIIIIIIIXXXXXXX
	}


	return DIRN_STOP; // if BOTH order lists empty, return dirn_stop
}
		/*motor_dir_g doesnt change
		else if (orders in the other direction)
			motor_dir_g is other direction
		else  
			direction = stop*/
	



	// looks at order lists
	// find the which direction to go in based on simplified lift algorithm (see stackoverflow)
	// return direction;

int orderListsEmpty() {
	for(int i=0; i<4; i+=1){
		if (order_priority_up[i] || order_priority_down[i]){
			return 0;
		}

	}
	return 1; 
}


void removeAllOrders(){
	for(int i=0;i<4;i+=1){
		order_priority_up[i]=0;
		order_priority_down[i]=0;
	}
	
	for(int i=0;i<4;i+=1){//
		for(int j = 0; j<=2;j+=1){
			if( !((i==0 && j==1) || (i==3 && j==0)) ){ // special cases
				//printf("floor: %i \n dir: %i",i,j );
				elev_set_button_lamp(j, i, 0);
			}
		}
	}
}


int isOrderInFloor(Floor floor) { // in the future this should be shouldLiftstop
	if (floor != UNDEFINED)
		return (order_priority_up[floor] || order_priority_down[floor]);
	else
		return 0;
}



// run EVERY time in FSM
// can change state of system, and change direction

/*void orderManager() {
	
	if (state == STOP){
		removeAllOrders();
		delete everything in list
		fuck with lights?
		osv
		return;
	}
		

	checkForOrders(); // this also adds new orders to the list

	dir = selectDir();// This changes direction of lift movement
	

	// state transistions can be done from main while(1) instead
	if (motor_dir_g != DIRN_STOP){ // can change names, remember consistensy!
		state = RUNNING;
	else{ 
		state = IDLE;
		}
	}
}
*/