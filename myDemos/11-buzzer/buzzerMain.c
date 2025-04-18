#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

static char secondCount = 0;
static int frequency = 1000;
static char step = 0;

int main() {
    configureClocks();
 
    buzzer_init();
    buzzer_set_period(2500);	/* start buzzing!!! 2MHz/1000 = 2kHz*/

    enableWDTInterrupts();
    or_sr(0x18);          // CPU off, GIE on
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= 250) { 	/* once each sec... */
    secondCount = 0;
    switch (step) {
      case 0:
        frequency = 2550;
        step++;
        break;
      case 1:
        frequency = 1911;
        step++;
        break;
      case 2:
        frequency = 1522;
        step++;
        break;
      case 3:
        frequency = 1275;
        step = 0;
        break;
      default:
        frequency = 2500;
    }
    buzzer_set_period(frequency);
  }
} 

//void
//__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
//{
//  secondCount ++;
//  if (secondCount >= 50) { 	/* once each sec... */
//    if (gDir) {
//      frequency += 50;
//    } else {
//      frequency -= 50;
//    }
//    
//    buzzer_set_period(frequency);
//
//    if (frequency<=1000) {
//      gDir = 1;
//    }
//
//    if (frequency >= 5000) {
//      gDir = 0;
//    }
//  }
//} 
