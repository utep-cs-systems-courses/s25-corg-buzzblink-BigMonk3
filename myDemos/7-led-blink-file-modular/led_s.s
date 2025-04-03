	.arch msp430g2553
	.p2align 1,0

  .data

red_on:
  .byte 0

green_on:
  .byte 0

led_changed:
  .byte 0
  
redVal:
  .byte 0
  .byte 0x01

greenVal:
  .byte 0
  .byte 0x40

  .align 2

  .equ LEDS, 0x41

  .extern P1DIR
  .extern P1OUT

  .global red_on
  .global green_on
  .global led_changed

  .global led_update
  .global led_init

  .text

led_init:
  bis #LEDS, &P1DIR
  mov #1, &led_changed
  call #led_update
  ret

led_update:
  cmp #0, &led_changed 
  jz end
  mov.b &green_on, r13
  mov.b greenVal(r13), r12
  mov.b &red_on, r13
  bis.b redVal(r13), r12
  mov #0xbe, r13
  bis.b r12, r13
  and.b r13, &P1OUT
  bis.b r12, &P1OUT
  mov #0, &led_changed
end:
  ret

