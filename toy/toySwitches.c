#include <msp430.h>
#include <libTimer.h>
#include "lcddraw.h"
#include <lcdutils.h>
#include "toyState.h"
#include "toySwitches.h"


static unsigned char switches_current;

void switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;

  switch_update_interrupt_sense();
}

unsigned int switch_read(){
  unsigned int sw_changed = switches_current^ switch_down;
  switch_down = switches_current;
  return switches_current | (sw_changed << 8);  
}


static void switch_update_interrupt_sense(){
    switches_current = P2IN & SWITCHES;
    P2IES |= (switches_current);   
  P2IES &= (switches_current | ~SWITCHES);
}

//buzzer initializer
void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &=  ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_off(){
  CCR0 = 0;
  CCR1 = 0;
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

unsigned char red_led = 0;
unsigned char green_led =0;
unsigned char leds_change = 0;
static char redVal[] =  {0, LED_RED};
static char greenVal[] = {0, LED_GREEN};

void led_init(){
  P1DIR |= LEDS;
  leds_change = 1;
  led_update();
}

void led_update(){
  if(leds_change){
    char ledFlags = redVal[red_led] | greenVal[green_led];

    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;
    leds_change = 0;
      
  }
}

void green_light(char ledBool){
  if(ledBool > 0)
    green_led = 1;
  else
    green_led = 0;

  leds_change = 1;
}

void red_light(char ledBool){
  if(ledBool > 0)
    red_led = 1;
  else
    red_led = 0;

  leds_change = 1;
  led_update();
}
int redraw(int screen){
  while(!redraw){
    P1OUT &= ~LED_RED;
    or_sr(0x10);
  }
  P1OUT |= LED_RED;
  return 0;
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {  
    P2IFG &= ~SWITCHES;     
    switch_update_interrupt_sense();
  }
}

//TODO: Fix clicking sound
void __interrupt_vec(WDT_VECTOR) WDT(){
  static char count = 0;
  static int current = 0; 
  char changed;
  //125
  if(++count == 2){
    //current = melody(current);
    state_advance();
     count =0;
    }
}
