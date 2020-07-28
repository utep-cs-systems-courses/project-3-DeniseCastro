#ifndef toySwitches_included
#define toySwitches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)

unsigned int switch_read();
void switch_init(unsigned char mask);
static void switch_update_interrupt_sense();

//Buzzer stuff
void buzzer_init();
void buzzer_off();
void buzzer_set_period(short cycles);

extern char switch_one_state;
extern char switch_two_state;
extern char switch_three_state;
extern char switch_four_state;
extern char switches_change;
int switch_down;

#endif
