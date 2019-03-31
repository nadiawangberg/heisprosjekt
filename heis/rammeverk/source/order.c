#include "elev.c"
void printOrders(){
	printf("order_priority_up: ")
	for (int i=0;i<4;i+=1){
			printf("%d ",order_priority_up[i])
	}
	printf("\n order_priority_down: ")
	for (int i=0;i<4;i+=1){
			printf("%d ",order_priority_down[i])
	}
}

/*int maxValOfList(int* list, int length){
	int max_val=list[0];
	for(int i = 1;i<length;i+=1){
		if(list[i]>max_val){
			max_val=list[i]
		}
	}
}*/

//Nadia suggestion, make a new struct NOT use elev_motor_direction_t for this


void addOrder(Floor floor, elev_motor_direction_t dir){
	if(dir==DIRN_UP){ // person wanting to go up
		order_priority_up[floor]=1;
		elev_set_button_lamp(BUTTON_UP,floor, 1);	
	}
	else if(dir==DIRN_DOWN){
		order_priority_down[floor]=1;
		elev_set_button_lamp(BUTTON_DOWN,floor, 1);
	}
	else{ // aka dir == DIRN_STOP, aka person in lift pressed button (1-4)
		elev_set_button_lamp(BUTTON_COMMAND,floor, 1);
		if(DIRECTION==DIRN_UP){
			order_priority_up[floor]=1;
		}
		else{ // Dir = down
			order_priority_down[floor]=1;
		}
	}
}
	

//hjelpe funksjon
	
// called in each floor, no matter what (prob 2 times for 1. and 4. floor)
bool removeOrders(){ //obv NOT done
	if(DIRECTION==DIRN_UP){
		if(order_priority_up[floor]==0)
			order_priority_up[floor]=0;
			elev_set_button_lamp(BUTTON_UP,floor, 0);
	}
	else if(order_priority_down[floor]==0){
		order_priority_down[floor]=0;
		elev_set_button_lamp(BUTTON_DOWN,floor, 0);
	} 
	elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
}


void checkForOrders(){//feels if we have orders (button press), adds them to queue if there are orders
	for(int i=0;i<4;i+=1){
		if(elev_get_button_signal(BUTTON_CALL_UP,i)){
			addOrder(DIRN_UP,i);
		}
		if(elev_get_button_signal(BUTTON_COMMAND,i)){
			addOrder(0,i);
		}
		if(elev_get_button_signal(BUTTON_CALL_DOWN,i)){
			addOrder(DIRN_DOWN,i);
		}
	}
}
void (){

}



int selectDir() {
	// looks at order lists
	// find the which direction to go in based on simplified lift algorithm (see stackoverflow)
	// return direction;

}

// run EVERY time in FSM
// can change state of system, and change direction
void orderManager() {
	/*
	if (state == stop state)
		delete everything in list
		fuck with lights?
		osv
		return;

	checkForOrders() // this also adds new orders to the list

	dir = selectDir() // This changes direction of lift movement
	

	// state transistions can be done from main while(1) instead
	if dir != stop / chillern: // can change names, remember consistensy!
		state = running
	else: 
		state = idle


	*/
}