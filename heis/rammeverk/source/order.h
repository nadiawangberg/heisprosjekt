#include "liftMovement.h"
"""typedef Struct tag_order {
	elev_motor_direction_t dir;
	int priority;
} Order;"""
int order_priority[4][2]={{0,0},{0,0},{0,0},{0,0}};
void addOrder(Floor floor,elev_motor_direction_t dir);
void removeOrder(Floor floor);
bool takeBonusOrder();
bool takeOrder();
void checkForOrderAndAddOrderToList();
void printOrders();