#include "elev.h"
#include "liftMovement.h"
#include "order.h"
#include "FSM.h"
#include <stdio.h>

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
    
    printf("Press STOP button to stop elevator and exit program.\n");


    elev_set_motor_direction(DIRN_UP); // kjører opp


    while (1) {   

        checkForOrders();
        printOrders();
        
        //elev_set_motor_direction(selectDir(SECOND,DIRN_UP));
        if(elev_get_floor_sensor_signal()==2){
            removeOrders(THIRD);
        }
    
    }
}
