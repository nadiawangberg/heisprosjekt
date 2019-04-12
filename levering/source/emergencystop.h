#ifndef __INCLUDE_STOP_H__
#define __INCLUDE_STOP_H__

#include "FSM.h"
#include "order.h"
/**
* @file
* @brief Emergency stop module, makes sure lift stops immediately and all orders removed when the stop button is pressed.
*/

/**
Initializes emergency stop state.
Immediately stops lift, sets stop lamp, removes all orders.
*/
void init_emergencystop();

#endif // #ifndef __INCLUDE_STOP_H__