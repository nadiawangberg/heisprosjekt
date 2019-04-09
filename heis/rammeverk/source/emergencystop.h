#ifndef __INCLUDE_STOP_H__
#define __INCLUDE_STOP_H__

#include "FSM.h"
#include "order.h"

/**
Initializes emergency stop state.
imediately stops lift, sets stop lamp, removes all orders
*/
void init_emergencystop();

#endif // #ifndef __INCLUDE_STOP_H__