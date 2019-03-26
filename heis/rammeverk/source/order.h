#include "liftMovement.h"
typedef Struct tag_order {
	elev_motor_direction_t dir;
	int priority;
} Order;
Order order_priority[6];
void addOrder(Floor floor);
void removeOrder(Floor floor);
bool takeBonusOrder();
bool takeOrder();
void checkForOrderAndAddOrderToList();
