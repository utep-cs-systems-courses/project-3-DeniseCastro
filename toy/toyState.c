#include <msp430.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "toySwitches.h"

void stateMachine(int pressed){
  int countdown = 0;
  
  switch(pressed){
  case 1:
    buzzer_set_period(7040);
  drawString5x7(10,10, "IN State ONE", COLOR_GREEN, COLOR_BLACK);
    break;
  case 2: buzzer_set_period(5587.65);
    drawString5x7(10,10, "IN State TWO", COLOR_GREEN, COLOR_BLACK);
    break;
  case 3: buzzer_set_period(4698.63);
drawString5x7(10,10, "IN State THREE", COLOR_GREEN, COLOR_BLACK);
    break;
  case 4: buzzer_set_period(5919.91);
drawString5x7(10,10, "IN State Four", COLOR_GREEN, COLOR_BLACK);
    break;

  default: buzzer_off();
     clearScreen(COLOR_BLACK);
    break;

    countdown++;
  }
}
