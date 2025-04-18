
#ifndef switches_included
#define switches_included

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SWITCHES 15

void led_init();
static char switch_update_interrupt_sense();
void switch_init();
void switch_interrupt_handler();

#endif

