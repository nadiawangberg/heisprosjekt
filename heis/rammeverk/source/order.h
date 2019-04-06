//#include "liftMovement.h"
#ifndef __INCLUDE_ORDER_H__
#define __INCLUDE_ORDER_H__
#include "liftMovement.h"

/*
typedef Struct tag_order {
	elev_motor_direction_t dir;
	int priority;
} Order;
*/


typedef enum tag_order_direction { 
    DOWN = -1,
    COMMAND, // inside lift
    UP
} order_direction_t;


//int order_priority_in[4][2]={{0,0},{0,0},{0,0},{0,0}};
//int order_priority_out[4][2]={{0,0},{0,0},{0,0},{0,0}};

// Not global, member variables for order
static int order_priority_up[4]={0,0,0,0};//initalized as  zero vector
static int order_priority_down[4]={0,0,0,0};

/**
  Add a order.
  @param dir Which direction type to check. Can be DOWN, COMMAND or UP.
  @param floor Which floor to add order. Must be 0-3.
  @return void.
*/
void addOrder(Floor floor, order_direction_t order_dir); // dir = order_direction
/**
  Removes all order in the current floor that goes in the elevators direction.
  @param floor Which floor to remove order in. Must be 0-3.
  @return void.
*/
void removeOrders(Floor floor);
 //removes all orders in the right direction in the current floor
/**
  Checks for incoming orders and adds them into lists.
  @return void.
*/
void checkForOrders(); 
/**
  Prints our current pending orders.
  @return void.
*/
void printOrders();
/**
  Selects which direction the elevator should move.
  @return a elev_motor_direction_t which can be DIRN_DOWN, DIRN_STOP or DIRN_UP.
*/
elev_motor_direction_t selectDir(Floor floor,elev_motor_direction_t current_direction); //
/**
  Removes all orders. 
  @return a elev_motor_direction_t which can be DIRN_DOWN, DIRN_STOP or DIRN_UP.
*/
void removeAllOrders(); //removes every order in every direction
/**
  Handling everything to do with orders in the FSM, recieves orders, changes lift direction, removes orders when done osv.
  @return void.
*/
void orderManager();


//idea #3: why not drop priority, it sucks either way.  

/* new idea, may suck. Have a number of orders above current floor. 
When we check to stop we just check the ligths lmao. 
The number of lights that are on are the amount of orders that.
*/


int shouldLiftstop(Floor floor);
/* 
  @return 1 if there are orders, 0 if there are no orders.
*/

#endif