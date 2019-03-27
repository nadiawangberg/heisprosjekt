#include "elev.c"
/*void printOrders(){
	for (int i=0;i<4;i+=1){
		for(int j=0;j<2;j+=1){
			printf("%d ",order_priority[i][j])
		}
		printf("\n")
	}
}*/
int maxValOfList(int* list, int length){
	int max_val=list[0];
	for(int i = 1;i<length;i+=1){
		if(list[i]>max_val){
			max_val=list[i]
		}
	}
}
void addOrder(Floor floor, elev_motor_direction_t dir){ //updated to work with separete order lists
	if(dir==0){
		if (order_priority_in[floor]==0) {
			order_priority_in[floor]=maxValOfList(order_priority_in,4)+1;	
		
	}
	else if {
		switch (floor){
			case FIRST:
				if (order_priority_out[0]==0){
					order_priority_out[0]=maxValOfList(order_priority_out,6)+1;
				}
			case SECOND:
				if(order_priority_out[1+dir==DIRN_UP]==0){
					order_priority_out[1+dir==DIRN_UP]=maxValOfList(order_priority_out,6)+1;
				}
			case THIRD:
				if(order_priority_out[3+dir==DIRN_UP]==0){
					order_priority_out[3+dir==DIRN_UP]=maxValOfList(order_priority_out,6)+1;
				}
			case FOURTH:
				if (order_priority_out[5]==0){
					order_priority_out[5]=maxValOfList(order_priority_out,6)+1;
				}
		}
		}
	}
	/*if(dir==0){
		if(current_floor>floor){
			order_priority[floor][0];
		}
		else{
			order_priority[floor][1];
		}
	}                                        //old garbage 
	else if(dir==DIRN_DOWN){
			order_priority[floor][0];
		}
	else{
			order_priority[floor][1];
		}
		*/
}

void removeOrder(Floor floor,elev_motor_direction_t dir){
	
	if(dir==0){
		order_priority_in[floor]=0;	 //lights needs to be fixed
	}
	else if {
		switch (floor){
			case FIRST:
					order_priority_out[0]=0;

		
			case SECOND:
					order_priority_out[1+dir==DIRN_UP]=0;

			case THIRD:
					order_priority_out[3+dir==DIRN_UP]=0;

			case FOURTH:
					order_priority_out[5]=0;
				
		}
		}
	}






	/*elev_set_button_lamp(BUTTON_COMMAND,floor, 0);
	order_priority[floor][dir==DIRN_UP]
	if(dir==DIRN_UP){
		elev_set_button_lamp(BUTTON_UP,floor, 0);
		order_priority[floor][1]=0;
	}
	else{
		elev_set_button_lamp(BUTTON_DOWN,floor, 0);
		order_priority[floor][0]=0;
	}*/
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
bool takeBonusOrder(){ //obv not done
	if(order_priority_in[current_floor]>1){
		removeOrder(floor,0);
	}
	if(current_floor>last_floor){

		removeOrder(floor,DIRN_UP)
	} 
	/*
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
	*/
}
bool takeOrder(){

}
void checkForOrderAndAddOrderToList(){

}