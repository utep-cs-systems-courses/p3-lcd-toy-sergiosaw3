# makfile configuration

COMMON_OBJECTS		= draw_shapes.o wdtInterruptHandler.o switches.o led.o p2_c_handler.o p2_asm_handler.o lcddraw.o buzzer.o

CPU             	= msp430g2553

CFLAGS          	= -mmcu=${CPU} -Os -I../h

LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/



#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc

AS              = msp430-elf-gcc -mmcu=${CPU} -c



all: main.elf



#additional rules for files

main.elf: ${COMMON_OBJECTS} main.o

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd



load: main.elf

	msp430loader.sh $^



clean:
	rm -f *.o *.elf
