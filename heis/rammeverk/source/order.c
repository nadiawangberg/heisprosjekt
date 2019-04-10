#include "order.h"


void print_order(){
	printf("order_up_m: ");
	for (int i=0;i<4;i+=1){
			printf("%d ",order_up_m[i]);
	}
	printf("\n order_down_m: ");
	for (int i=0;i<4;i+=1){
			printf("%d ",order_down_m[i]);
	}
}


void addOrder_order(Floor floor, order_type_t order_type){
	if(order_type==UP){
		order_up_m[floor]=1;
		elev_set_button_lamp(BUTTON_CALL_UP,floor, 1);	
	}
	else if(order_type==DOWN){
		order_down_m[floor]=1;
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 1);
	}
	else if (order_type==COMMAND){
		elev_set_button_lamp(BUTTON_COMMAND,floor, 1);
		order_down_m[floor]=1;
		order_up_m[floor]=1;
		}
	}
	

void removeOrders_order(Floor floor){
	order_up_m[floor]=0;
	order_down_m[floor]=0;

	if (floor != FOURTH) {
		elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
	}

	if (floor != FIRST) {
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor, 0);
	}

	elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
}


void checkForOrders_order(){
	for(int i=0;i<4;i+=1){
		if(i!=3 && elev_get_button_signal(BUTTON_CALL_UP,i)){ // this results in elev_get_button_signal(BUTTON_CALL_UP,3) never being called
			addOrder_order(i,UP);
		}
		if(elev_get_button_signal(BUTTON_COMMAND,i)){
			addOrder_order(i,COMMAND);
		}
		if(i!=0 && elev_get_button_signal(BUTTON_CALL_DOWN,i)){ // this results in elev_get_button_signal(BUTTON_CALL_DOWN,0) never being called
			addOrder_order(i,DOWN);
		}
	}
}


elev_motor_direction_t selectDir_order(float inbetween_floor, elev_motor_direction_t current_direction) {

	Floor floor = (int)inbetween_floor;

	switch(current_direction){
		case DIRN_UP:
			for(int i=floor+1;i<4;i+=1){
				if(order_up_m[i]||order_down_m[i]){ //sjekker om det er flere bestillinger å ta oppover
					return DIRN_UP;
				}
			}
			for(int i=floor-1;i>=0;i-=1){
				if(order_up_m[i]||order_down_m[i]){ //sjekker bestillinger under etter sjekket bestillinger over, dermed blir bestilling over prioritert
					return DIRN_DOWN;
				}
			}
			return DIRN_STOP;
		case DIRN_DOWN:
			for(int i=floor-1;i>=0;i-=1){
				if(order_up_m[i]||order_down_m[i]){ //motsatt av casen med dirn_up
					return DIRN_DOWN;
				}
			}
			for(int i=floor+1;i<4;i+=1){
				if(order_up_m[i]||order_down_m[i]){
					return DIRN_UP;
				}
			}  
			return DIRN_STOP;                                                                                                                                              
		case DIRN_STOP: //fra kun idle
		
			// to satisify CASE S8 (from kravspesifikasjon)
			if ((order_up_m[floor] || order_down_m[floor]) && inbetween_floor != floor) {
				return DIRN_DOWN;
			}

			for(int i=floor+1;i<4;i+=1){ 
				if(order_up_m[i] || order_down_m[i]){ //sjekker om vi har noen bestillinger over heisen
					return DIRN_UP;
				}
			}
			for(int i=floor-1;i>=0;i-=1){
				if(order_up_m[i] || order_down_m[i]){ //sjekker om vi har noen bestillinger over heisen
					return DIRN_DOWN;
				}
			}
			return DIRN_STOP;
		}
}


int orderListsEmpty_order() {
	for(int i=0; i<4; i+=1){
		if (order_up_m[i] || order_down_m[i]){
			return 0;
		}
	}
	return 1; 
}


void removeAllOrders_order(){
	for(int i=0;i<4;i+=1){
		order_up_m[i]=0;
		order_down_m[i]=0;
	}
	
	for(int i=0;i<4;i+=1){
		for(int j = 0; j<=2;j+=1){
			if( !((i==0 && j==1) || (i==3 && j==0)) ){ // special cases
				elev_set_button_lamp(j, i, 0);
			}
		}
	}
}


int shouldLiftStop_order(Floor floor,elev_motor_direction_t motor_dir_g) {
	switch(floor){
		case(FIRST):
		case(FOURTH):
			return order_down_m[floor] || order_up_m[floor]; // if order in 1. / 4. stop
		case(SECOND):
		case(THIRD): 
			if(motor_dir_g==DIRN_UP){
				if(order_up_m[floor]){ // order in correct direction (up)
					return 1;
				}
				else if(order_down_m[floor]){ //order in opposite direction (down)
					for(int i=floor+1;i<4;i+=1){ 				
						if(order_down_m[i] || order_up_m[i]){  //check if there are orders above
							return 0; 						//orders above -> dont stop
						}
					}
					return 1; //no orders above -> stop
				}
			}
			else if(motor_dir_g==DIRN_DOWN){ 
				if(order_down_m[floor]){ // order in correct direction (down)
					return 1;
				}
				else if(order_up_m[floor]){ //order in opposite direction (down)
					for(int i=0;i<floor;i+=1){
						if(order_up_m[i] || order_down_m[i]){ //check if there are orders below
							return 0;						//orders below ->dont stop
						}
					}
					return 1; //no orders below -> stop
				}
			}
		case(UNDEFINED):
			return 0; //if we are not in a floor there are no orders to stop for.
	}
	return 0;
 }

int isOrderInFloor_order(Floor floor) {
	if (floor != UNDEFINED) {
		return (order_up_m[floor] || order_down_m[floor]);
	}
	else {
		return 0;
	}
}