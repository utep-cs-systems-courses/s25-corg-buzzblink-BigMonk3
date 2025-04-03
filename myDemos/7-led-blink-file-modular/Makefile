# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: blink_c.elf blink_s.elf

#additional rules for files
blink_c.elf: ${COMMON_OBJECTS} blinkMain.o stateMachines.o led_c.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load-c: blink_c.elf
	msp430loader.sh blink_c.elf

blink_s.elf: ${COMMON_OBJECTS} blinkMain.o stateMachines.o led_s.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load-s: blink_s.elf
	msp430loader.sh blink_s.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h
