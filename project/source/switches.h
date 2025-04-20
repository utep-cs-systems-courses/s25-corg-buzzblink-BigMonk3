
#ifndef switches_included
#define switches_included

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SSW BIT3 // side switch is P1.3

#define SWITCHES 15

static char switch_update_interrupt_sense();
static char side_switch_update_interrupt_sense();

void switch_init();
void side_switch_init();

void switch_interrupt_handler();
void side_switch_interrupt_handler();

#endif

