//#include "liftMovement.h"
#ifndef __INCLUDE_ORDER_H__
#define __INCLUDE_ORDER_H__
#include "liftMovement.h"

typedef enum tag_order_type { 
    DOWN = -1,
    COMMAND, // inside lift
    UP
} order_type_t;

// Not global, member variables for order
static int order_priority_up[4]={0,0,0,0};//initalized as  zero vector
static int order_priority_down[4]={0,0,0,0};

/**
  Prints our current pending orders.
*/
void printOrders();

/**
  Add an order to one/both of the order_priority lists
  @param order_type Which order type we have. Can be DOWN (outside lift down button), COMMAND (inside lift any button) or UP (outside lift up button).
  @param floor Which floor the lift is ordered to go to. Must be 0-3.
*/
void addOrder(Floor floor, order_type_t order_type); // dir = order_direction

/**
  Removes all order in inputed floor, and turns off corresponding order button lights
  @param floor Which floor to remove order in. Must be 0-3.
*/
void removeOrders(Floor floor);

/**
  Checks for incoming orders and adds them to lists (by calling addOrder function)
*/
void checkForOrders(); 

/**
  Selects which direction the elevator should move.
  @return a elev_motor_direction_t which can be DIRN_DOWN, DIRN_STOP or DIRN_UP.
*/
elev_motor_direction_t selectDir(float inbetween_floor, elev_motor_direction_t current_direction);

/**
  Removes all orders. 
*/
void removeAllOrders(); //removes every order in every direction


/**
  @param floor Which floor to check for orders
  @return 1 if there is an order i floor, 0 if there are none.
*/
int isOrderInFloor(Floor floor);


/**
  @param floor The floor the lift should consider stopping in.
  @param motor_dir The direction the lift is currently moving in.
  @return 1 if the lift should stop, 0 if the lift shouldnt. 
*/
int shouldLiftStop(Floor floor,elev_motor_direction_t motor_dir);

/**
  @return 1 if there are any orders, 0 if there are no orders.
*/
int areOrderListsEmpty();

/**
  allows lift to always know its position, even between floors
  THIS FUNCTION ISNT EVEN USED ANYMORE!!
*/
float getInbetweenFloor(Floor floor, elev_motor_direction_t motor_dir_g);


#endif