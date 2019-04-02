#include "elev.h"
#include "liftMovement.c"
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
    DIRECTION=DIRN_UP;
    while (1) {
        // Change direction when we reach top/bottom floor
     /*   if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // HEIS TEST
        elev_set_door_open_lamp(1);
        elev_set_stop_lamp(1);
        elev_set_floor_indicator(2);
        elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 1);
*/      

        checkForOrders();
        printOrders();

/*

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
    */
    //elev_set_motor_direction(DIRN_UP);

  //  positionInit();
 //printf("\n%i\n",current_floor);
   // return 0;
}
}
