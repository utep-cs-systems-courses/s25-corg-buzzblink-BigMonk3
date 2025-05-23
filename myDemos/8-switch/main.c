#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

static char secondCount = 0;
static char blinkSpeed = 1;

void main(void) 
{  
  configureClocks();

  P1DIR |= LEDS;
  P1OUT &= ~LED_RED;		/* red initially off */
  P1OUT |= LED_GREEN;		/* green initially on */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  enableWDTInterrupts();
  or_sr(0x18);  // CPU off, GIE on
} 

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  // P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  
  if (blinkSpeed < 11) {
    blinkSpeed++;
  } else {
    blinkSpeed = 1;
  }
}


/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= 250/blinkSpeed) { 	/* once each sec... */
    secondCount = 0;		/* reset count */
    P1OUT ^= LED_GREEN;		/* toggle green LED */
    P1OUT ^= LED_RED;
  }
} 

