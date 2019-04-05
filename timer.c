#include <stdio.h>
#include <time.h>

int msec = 0, trigger = 3000; /* 10ms */
int math = 2;
int iterations = 0;
clock_t difference; // time_passed, stop_watch_time, time_diff
clock_t before;

int timerDone() {
  difference = clock() - before;
  msec = difference * 1000 / CLOCKS_PER_SEC;
  //printf("difference: %d \n", msec);
  return (msec >= trigger);
}

void initTimer() {
  printf("INIT TIMER \n");
  msec = 0;
  before = clock();
}

int main(void) {
  initTimer();
  
  while(1) {
    if (timerDone()) { // needs to be run in order for tim
      printf("\n timer done! \n");
      initTimer();
      //break;
    }

    // other garbage in while loop
    iterations++;
    math += (math * iterations) / math ; 
  }

//printf("Time taken %d seconds %d milliseconds (%d iterations)\n",
//  msec/1000, msec%1000, iterations);
  
}

