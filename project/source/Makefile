
# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: bugle.elf 

#additional rules for files
bugle.elf: ${COMMON_OBJECTS} buzzer.o switches.o bugle.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: bugle.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf

buzzer.o: buzzer.c buzzer.h
switches.o: switches.c switches.h
bugle.o: bugle.c
