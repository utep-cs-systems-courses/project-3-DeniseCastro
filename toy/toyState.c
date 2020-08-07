#include <msp430.h>
#include <lcdutils.h>
#include "lcddraw.h"
#include "toySwitches.h"

char melodyIn = 0;

//TODO: Fix clicking sound
int melody(int current){
  short note = 0;
 
   switch(++current){
    case 0: note = 3520; break;
    case 1: note = 4698.63; break;
    case 2: note = 5587.65; break;
    case 3: note = 3951.07; break;
    case 4: note = 5274.04; break;
   case 5: note = 4698.63; current = 0; melodyIn = 0; break;
    }
   if(melodyIn)   
    buzzer_set_period(note);

  return current;
}

void checkKey(int* key){
  int keyBool = 0;
  
  for(int i =  0; i <= 4; i++)
    keyBool += (key[i]==i)?1: 0;
  if(keyBool == 5){
    drawString5x7(30,30,"KEY Found", COLOR_RED, COLOR_BLACK);
    melodyIn=1;
  }

  keyBool=0;
}


char toggle_green(){
  static char state = 0;

  switch(state){
  case 0: green_led = state = 1; break;
  case 1: green_led = state = 0; break;
  }

  return 1;
}


void state_advance(){
  char changed = 0;
  static int state = 0;

  switch(state){
  case 0: changed = toggle_green(); state++; break;
  case 1: changed = toggle_green(); state--; break;
  }
  leds_change = changed;
  led_update();
}

void stateMachine(int pressed){
  short note = 0;
  char* str;
  static int key[] = {0,0,0,0,0};
  int keyBool = 0;
  
  switch(pressed){
  case 1:
    note = 3729.31; //NOTE A#
    str = "VINES ";
    key[pressed] = (key[3] == 3)? 1: 0;
    vines(0,30,13,COLOR_GREEN);
    
    break;
  case 2:
    note = 4434.92; // NOTE C#
    str = "FLOWER ";
    key[pressed] = (key[0] ==0)? 2: 0;
    roses(25, COLOR_WHITE);
    roses(25, COLOR_RED);
    break;
  case 3:
    note = 4978.03;  // NOTE D#
    str = "DIM";
    key[pressed] = (key[4] == 4)? 3: 0;
    green_light(0);
    led_update();
    fillRectangle(0,16,screenWidth, screenHeight,COLOR_BLACK);
    break;
  case 4:
    note = 5919.91;;  // NOTE F#
    str = "KEY: start w/ 2";
    key[pressed] = (key[2] == 2) ? 4: 0;
    roses(25,COLOR_PINK);
    break;
  default: buzzer_off();
    str = "                         ";
  fillRectangle(0,16,screenWidth, screenHeight,COLOR_BLACK);
    break;
  }

  checkKey(key);

  buzzer_set_period(note);
    
  drawString5x7(1,1, str, COLOR_GREEN, COLOR_BLACK);
  
}
