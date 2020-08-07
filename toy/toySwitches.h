#ifndef toySwitches_included
#define toySwitches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)

#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0|BIT6)

unsigned int switch_read();
void switch_init();
static void switch_update_interrupt_sense();

void led_init();
void led_update();
void green_light(char ledBool);
void red_light(char ledBool);

//Buzzer stuff
void buzzer_init();
void buzzer_off();
void buzzer_set_period(short cycles);

//variables
extern char count;
extern char switches_change;
extern unsigned char red_led;
extern unsigned char green_led;
extern unsigned char leds_change;
int switch_down;

int redraw(int);
#endif
