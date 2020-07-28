#include <msp430.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "toySwitches.h"

void stateMachine(int pressed){
  int countdown = 0;
  
  switch(pressed){
  case 1: buzzer_set_period(7040); break;
  case 2: buzzer_set_period(5587.65); break;
  case 3: buzzer_set_period(4698.63); break;
  case 4: buzzer_set_period(5919.91); break;

  default break;
    
  }
}
