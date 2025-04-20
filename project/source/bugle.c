#include <msp430.h>
#include "bugle.h"
#include "switches.h"

int bugle_controller(int switches) {
  int frequency = 0;

  if (switches & SW1) {
    frequency = NOTE_G5;
  }

  if (switches & SW2) {
    frequency = NOTE_C6;
  }

  if (switches & SW3) {
    frequency = NOTE_E6;
  }

  if (switches & SW4) {
    frequency = NOTE_G6;
  }

  return frequency;
}
