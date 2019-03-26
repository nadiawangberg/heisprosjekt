#include "elev.h"
#include "FSM.h"
#include <stdio.h>
#include <time.h>

/**
* @file
* @brief The main file, it does what
* main files usually does
*/

State_t state = INIT; // Global state variable


// Global time
int msec = 0, trigger = 10; /* 10ms */
clock_t before = clock();

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");


    // TEST FOR DOOR + FSM
    elev_set_motor_direction(DIRN_UP); // kjører opp
    state = RUNNING;

    if (elev_get_floor_sensor_signal() == 2) {
        state = DOOR_OPEN;
        // start timer
    }

    StateMachine();

    /*
    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // HEIS TEST
        elev_set_door_open_lamp(1);
        elev_set_stop_lamp(1);
        elev_set_floor_indicator(2);
        elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 1);


        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
    */

    return 0;
}
