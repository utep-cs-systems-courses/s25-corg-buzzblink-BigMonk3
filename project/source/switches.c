#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "buzzer.h"

void
led_init() { 
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches;
char ledPattern;

void
switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
  int frequency = 0;
  P1OUT &= ~LEDS;

  if (switches & SW1) {
    frequency = NOTE_G5;
    ledPattern = 0;
  }

  if (switches & SW2) {
    frequency = NOTE_C6;
    ledPattern = LED_RED;
  }

  if (switches & SW3) {
    frequency = NOTE_E6;
    ledPattern = LED_GREEN;
  }

  if (switches & SW4) {
    frequency = NOTE_G6;
    ledPattern = LED_RED | LED_GREEN;
  }

  P1OUT |= ledPattern;
  buzzer_set_period(frequency);
}


void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

