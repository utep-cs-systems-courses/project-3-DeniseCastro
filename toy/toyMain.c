#include <libTimer.h>
#include <lcdutils.h>
#include "lcddraw.h"
#include "toySwitches.h"
#include "toyState.h"

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
  
    if(!(switches & 1)  ) stateNum =1;
    else if(!(switches & 2)) stateNum =2;
    else if(!(switches & 4)) stateNum = 3;
    else if(!(switches & 8)) stateNum=4;
    
    stateMachine(stateNum);
  screen = redraw(screen);
     }
}
