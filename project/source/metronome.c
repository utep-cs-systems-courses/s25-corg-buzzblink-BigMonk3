#include <msp430.h>
#include <libTimer.h>
#include "metronome.h"

int secondCount;
int beatCount = 0;
int tempo = 250;

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount++;
  
  if (secondCount % 10 == 0) {
    P1OUT &= ~LEDS;
  }
  
  if (secondCount >= tempo) { 
    secondCount = 0;
    P1OUT |= LED_GREEN;	
j
    beatCount++;
    if (beatCount == 4) {
      P1OUT |= LED_RED;
      beatCount = 0;
    }
  }
}

void tempo_controller() {
  switch (tempo) {
    case 250:
      tempo = 167;
      break;
    case 167:
      tempo = 83;
      break;
    default:
      tempo = 250;
      break;
  }
}


