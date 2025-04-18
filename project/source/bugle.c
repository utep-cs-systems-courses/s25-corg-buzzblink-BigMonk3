
#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"

int main() {
  configureClocks();
  
  switch_init();
  buzzer_init();
  led_init();
  
  or_sr(0x18); //cpu off GIE set
}
