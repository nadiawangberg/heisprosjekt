#include "elev.c"
void printOrders(){
	for (int i=0;i<4;i+=1){
		for(int j=0;j<2;j+=1){
			printf("%d ",order_priority[i][j])
		}
		printf("\n")
	}
}
void addOrder(Floor floor, elev_motor_direction_t dir){
	if(dir==0){
		if(current_floor>floor){
			order_priority[floor][0];
		}
		else{
			order_priority[floor][1];
		}
	}
	else if(dir==DIRN_DOWN){
			order_priority[floor][0];
		}
	else{
			order_priority[floor][1];
		}
}

void removeOrder(Floor floor,elev_motor_direction_t dir){
	elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
	order_priority[floor][dir==DIRN_UP]
	if(dir==DIRN_UP){
		elev_set_button_lamp(BUTTON_UP,floor, 0);
		order_priority[floor][1]=0;
	}
	else{
		elev_set_button_lamp(BUTTON_DOWN,floor, 0);
		order_priority[floor][0]=0;
	}
    /*
	switch(floor):
		case FIRST:{
			order_priority[0]=0;
			elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
			break;
		}
		case SECOND:{
			if (dir==DIRN_DOWN){
				order_priority[1]=0;
			}
			else{
				elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
				order_priority[2]=0;
			}
			break;
		}
		case THIRD:{
			if (dir==DIRN_DOWN){
				order_priority[3]=0;
			}
			else{
				order_priority[4]=0;
				elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
			}
			break;
		}
		case FOURTH:{
			order_priority[5]=0;
			elev_set_button_lamp(BUTTON_CALL_UP,floor, 0);
			break;
		}
		*/

	return
}
bool takeBonusOrder(){
	if (current_floor>last_floor){
		if(order_priority[current_floor][1]>0){
			order_priority[current_floor][1]=0;
		}
	}
	else{
		if(order_priority[current_floor][0]>0){
			order_priority[current_floor][0]=0;
		}
	}
}
bool takeOrder(){

}
void checkForOrderAndAddOrderToList(){

}