#include <libTimer.h>
#include <lcdutils.h>
#include "lcddraw.h"
#include "toySwitches.h"
#include "toyState.h"

void main(){
  configureClocks();
  lcd_init();
  switch_init(15);
  buzzer_init();
  or_sr(0x8);

  //u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  while(1){
    u_int switches = switch_read();
    
    stateMachine(switches);
   }
}
