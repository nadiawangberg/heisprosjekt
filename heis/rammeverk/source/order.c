
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
		order_priority_down[floor]=1;
		order_priority_up[floor]=1;
		}
	}
		/*
		if(motor_dir_g==DIRN_UP){
			order_priority_up[floor]=1;
		}
		else if (motor_dir_g==DIRN_DOWN){ // Dir = down
			order_priority_down[floor]=1;
		}
		else if (motor_dir_g==DIRN_STOP) {
			// NOOOOOOOOO FIIIIIIIIIIIIIXXXX!!!!
			order_priority_up[floor]=1;
		}
		*/
	
	


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

// NB PASS PÅ AT TING IKKE
elev_motor_direction_t selectDir(float inbetween_floor, elev_motor_direction_t current_direction) { //Add edge case. Add case where pick up order under elev going up.


	floor = (int)inbetween_floor;

	switch(current_direction){
		case DIRN_UP:
			for(int i=floor+1;i<4;i+=1){
				if(order_priority_up[i]||order_priority_down[i]){ // sjekker om det er flere bestillinger å ta oppover
					return DIRN_UP;
				}
			}
			for(int i=floor-1;i>=0;i-=1){
				if(order_priority_up[i]||order_priority_down[i]){ //sjekker bestillinger under etter sjekket bestillinger over, dermed blir bestilling over prioritert
					return DIRN_DOWN;
				}
			}
			return DIRN_STOP;
		case DIRN_DOWN:
			for(int i=floor-1;i>=0;i-=1){
				if(order_priority_up[i]||order_priority_down[i]){ //motsatt av casen med dirn_up
					return DIRN_DOWN;
				}
			}
			for(int i=floor+1;i<4;i+=1){
				if(order_priority_up[i]||order_priority_down[i]){
					return DIRN_UP;
				}
			}  
			return DIRN_STOP;                                                                                                                                              
		case DIRN_STOP: //fra idle (inbetween_floor could be 0.5, 1.5, 2.5)

			// CHECK FOR SPECIAL CASE S8
			if ((order_priority_up[floor] || order_priority_down[floor]) && inbetween_floor != floor) {
				return DIRN_DOWN;
			}
			// DONE S8

			for(int i=floor+1;i<4;i+=1){ 
				if(order_priority_up[i] || order_priority_down[i]){ //sjekker om vi har noen bestillinger over heisen
					return DIRN_UP;
				}
			}
			for(int i=floor-1;i>=0;i-=1){
				if(order_priority_up[i] || order_priority_down[i]){ //sjekker om vi har noen bestillinger over heisen
					return DIRN_DOWN;
				}
			}
			return DIRN_STOP;
		}
}
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


int shouldLiftStop(Floor floor,elev_motor_direction_t motor_dir_g) {
	switch(floor){
		case(FIRST):
		case(FOURTH):
			return order_priority_down[floor] || order_priority_up[floor];
		case(SECOND):
		case(THIRD):
			if(motor_dir_g==DIRN_UP){
				if(order_priority_up[floor]){
					return 1;
				}
				else if(order_priority_down[floor]){
					for(int i=floor+1;i<4;i+=1){
						if(order_priority_down[i] || order_priority_up[i]){
							return 0;
						}
					}
					return 1;
				}
			}
			else if(motor_dir_g==DIRN_DOWN){
				if(order_priority_down[floor]){
					return 1;
				}
				else if(order_priority_up[floor]){
					for(int i=0;i<floor;i+=1){
						if(order_priority_up[i] || order_priority_down[i]){
							return 0;
						}
					}
					return 1;
				}
			}
		case(UNDEFINED):
			return 0;
	}
	return 0;
 }

int isOrderInFloor(Floor floor) {
	if (floor != UNDEFINED) {
		return (order_priority_up[floor] || order_priority_down[floor]);
	}
	else {
		return 0;
	}
}