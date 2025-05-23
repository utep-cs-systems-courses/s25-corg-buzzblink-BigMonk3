#ifndef metronome_included
#define metronome_included

#define LED_GREEN BIT0               // P1.0
#define LED_RED BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();
void tempo_controller();
void metronome_click();

extern int tempo;

#endif
