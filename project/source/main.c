
#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"
#include "metronome.h"

int main() {
  configureClocks();
  enableWDTInterrupts();
  
  
  switch_init();
  side_switch_init();
  buzzer_init();
  led_init();
  
  or_sr(0x18); //cpu off GIE set
}

int secondCount;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount++;
  
  if (secondCount % 10 == 0) {
    P1OUT &= ~LEDS;
  }
  
  if (secondCount >= tempo) { 
    secondCount = 0;
    metronome_click();
  }
}

