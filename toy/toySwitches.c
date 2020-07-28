#include <msp430.h>
#include <libTimer.h>
#include "toySwitches.h"

static unsigned char switch_mask;
static unsigned char switches_current;

void switch_init(unsigned char mask){
  switch_mask = mask;
  P2REN |= mask;
  P2IE = mask;
  P2OUT |= mask;
  P2DIR &= ~mask;

  switch_update_interrupt_sense();
}

unsigned int switch_read(){
  unsigned int sw_changed = switches_current^ switch_down;
  switch_down = switches_current;
  return switches_current | (sw_changed << 8);
}

static void switch_update_interrupt_sense(){
    switches_current = P2IN & switch_mask;
  P2IES |= (switches_current); 
  P2IES &= (switches_current | ~switch_mask); 
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


void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & switch_mask) {  
    P2IFG &= ~switch_mask;     
    switch_update_interrupt_sense();
  }
}
