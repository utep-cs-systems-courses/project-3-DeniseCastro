#include <libTimer.h>
#include <lcdutils.h>
#include "lcddraw.h"
#include "toySwitches.h"
#include "toyState.h"
#include "stateSet.h"

int screen = 1;

void main(){
  configureClocks();
  lcd_init();
  switch_init(15);
  buzzer_init();
  led_init();
  or_sr(0x8);
  enableWDTInterrupts();
  //u_char width = screenWidth, height = screenHeight;
   clearScreen(COLOR_BLACK); 
     for(int i =0; i<screenWidth;i++)
      drawPixel(i,15,COLOR_RED);


   //NOTE: Melody clicking due to infinite loop
     while(1){
  u_int switches = switch_read();

  int stateNum = 0;
  
  stateNum = stateSet(switches);
    stateMachine(stateNum);
  screen = redraw(screen);
     }
}
