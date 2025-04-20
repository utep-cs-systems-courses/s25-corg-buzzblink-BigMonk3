  .arch msp430g2553
  .p2align 1, 0

  .data

beatCount:
  .word 0

tempo:
  .word 0

  .extern P1DIR
  .extern P1OUT
  .extern LEDS

  .equ LEDS, 0x41
  .equ LED_RED, 0x40
  .equ LED_GREEN, 0x1

  .global tempo

  .global led_init
  .global tempo_controller
  .global metronome_click

  .text

led_init:
  bis #LEDS, &P1DIR
  mov #0xffff, r12
  xor #LEDS, r12
  and r12, &P1OUT

tempo_controller:
  cmp #250, &tempo
  jz case250
  cmp #167, &tempo
  jz case167
  mov #250, &tempo
  jmp out
case250:
  mov #167, &tempo
  jmp out
case167:
  mov #83, &tempo
out:
  pop r0;
  
metronome_click:
  add #1, &beatCount
  bis #LED_GREEN, &P1OUT
  cmp #4, &beatCount
  jnz end
  mov #0, &beatCount
  bis #LED_RED, &P1OUT
end:
  pop r0

