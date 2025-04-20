#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "metronome.h"
#include "buzzer.h"
#include "bugle.h"

static char 
side_switch_update_interrupt_sense()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
side_switch_init()			/* setup switch */
{  
  P1REN |= SSW;		/* enables resistors for switches */
  P1IE |= SSW;		/* enable interrupts from switches */
  P1OUT |= SSW;		/* pull-ups for switches */
  P1DIR &= ~SSW;		/* set switches' bits for input */
  switch_update_interrupt_sense();
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
switch_init() {
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */

  switch_update_interrupt_sense();
}

int switches;
char p2val;
char p1val;

void
switch_interrupt_handler() {
  p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;

  int frequency = bugle_controller(switches);

  buzzer_set_period(frequency);
}


void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}


void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SSW) {	     
    P1IFG &= ~SSW;		    
    tempo_controller();
  }
}

