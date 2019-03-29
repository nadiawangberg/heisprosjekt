#include "liftMovement.h"

/*
typedef Struct tag_order {
	elev_motor_direction_t dir;
	int priority;
} Order;
*/

//int order_priority_in[4][2]={{0,0},{0,0},{0,0},{0,0}};
//int order_priority_out[4][2]={{0,0},{0,0},{0,0},{0,0}};

// Not global, member variables for order
bool order_priority_up[4]={0,0,0,0};
bool order_priority_down[4]={0,0,0,0};

// probably global?
elev_motor_direction_t DIRECTION;


void addOrder(Floor floor, elev_motor_direction_t dir); // dir = order_direction
void removeOrder(Floor floor); //removes a single order
 //removes all orders in the right direction in the current floor
void checkForOrders(); 
void printOrders();

//vent med
bool takeOrder(); // maskineri, bevegelse osv, burde dette være i denne modulen??



//idea #3: why not drop priority, it sucks either way.  

/* new idea, may suck. Have a number of orders above current floor. 
When we check to stop we just check the ligths lmao. 
The number of lights that are on are the amount of orders that.
*/