#include "elev.h"
#include "liftMovement.h"
#include "FSM.h"
#include "door.h"
//#include "order.h"
#include <stdio.h>
#include <time.h>

/**
* @file
* @brief The main file, it does what
* main files usually does
*/
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    StateMachineInit();

    // Code is STUCK in this func atm
    StateMachine();
    return 0;
}
