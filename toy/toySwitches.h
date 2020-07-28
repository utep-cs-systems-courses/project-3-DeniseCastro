#ifndef toySwitches_included
#define toySwitches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)

unsigned int switch_read();
void switch_init();
static char switch_update_interrupt_sense();

//Buzzer stuff
void buzzer_init();
void buzzer_off();
void buzzer_set_period(short cycles);

char switch_one_state;
char switch_two_state;
char switch_three_state;
char switch_four_state;
char switches_change;
int switch_down;

#endif
