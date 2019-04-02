
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



//Nadia suggestion, make a new struct NOT use elev_motor_direction_t for this


void addOrder(Floor floor, elev_order_direction_t dir){
	if(dir==UP){ // person wanting to go up
		order_priority_up[floor]=1;
		elev_set_button_lamp(BUTTON_CALL_UP,floor, 1);	
	}
	else if(dir==DOWN){
		order_priority_down[floor]=1;
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 1);
	}
	else{ // aka dir == DIRN_STOP, aka person in lift pressed button (1-4)
		elev_set_button_lamp(BUTTON_COMMAND,floor, 1);
		if(DIRECTION==UP){
			order_priority_up[floor]=1;
		}
		else{ // Dir = down
			order_priority_down[floor]=1;
		}
	}
}
	

//hjelpe funksjon
	
// called in each floor, no matter what (prob 2 times for 1. and 4. floor)
void removeOrders(){ 
	if(DIRECTION==DIRN_UP){
		if(order_priority_up[floor]==0)
			order_priority_up[floor]=0;
			elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
	}
	else if(order_priority_down[floor]==0){
		order_priority_down[floor]=0;
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 0);
	} 
	elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
}


void checkForOrders(){//feels if we have orders (button press), adds them to queue if there are orders
	for(int i=0;i<3;i+=1){
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


/*elev_motor_direction_t selectDir(Floor floor, elev_motor_direction_t current_direction) {
	// if (more orders in the current direction)
	if (current_direction==DIRN_UP){
		for(int i=floor+1;i<=3,i+=1){
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
		for(int i=floor+1;i<=3,i+=1){
			if(order_priority_up[i]){
				return DIRN_UP;
			}
		}
	}
	else {return DIRN_STOP;}
	}
		DIRECTION doesnt change
		else if (orders in the other direction)
			DIRECTION is other direction
		else  
			direction = stop
	*/



	// looks at order lists
	// find the which direction to go in based on simplified lift algorithm (see stackoverflow)
	// return direction;
/*
void removeAllOrders(){
	order_priority_up[4]={0,0,0,0};
	order_priority_down[4]={0,0,0,0};
	for(int i=0;i<4;i+=1){
		for(int j = 0; j<=2;j+=1){
		elev_set_button_lamp(j, i, 0);
		}
	}
}
*/
// run EVERY time in FSM
// can change state of system, and change direction
/*
void orderManager() {
	
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
	if (DIRECTION != STOP){ // can change names, remember consistensy!
		state = RUNNING;
	else{ 
		state = IDLE;
		}
	}
}
*/