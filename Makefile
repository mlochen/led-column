CC = avr-gcc
ARGS = -mmcu=atmega2560 -Os -Wall -std=gnu99

all:
	$(CC) $(ARGS) -o ledcolumn.hex *.c fx/*.c
