# led_column

The code in this repository is for an led effect lamp (type column). It consists of a base, that contains the power supply and the microcontroller, and a light column, which is illuminated from the inside by an led strip with 300 LEDs. The strip is wrapped around a pipe with a diameter of 5cm, so that it forms a spiral.

## Hardware
    +--------------+                                 +---------------+
    |              | +5V                         Vcc |               |
    | Power supply |-----------+---------------------|               |
    |              | GND       |                 GND |    WS2812B    |
    |   5V / 18A   |-----------C------+--------------|               |
    |              |           |      |      DATA IN | 300 LEDs (5m) |
    +--------------+           |      |      +-------|               |
                               |      |      |       |               |
                           Vcc |  GND |  PD7 |       +---------------+
                           +---------------------+
                           |      AtMega2560     |
                           +---------------------+

![Photo](photo.jpg)

The power supply and the controller are in the base. The whole structure has a height of 125cm and a diameter of 16cm.

## How to build the software

1. run "make" in the base dir of the repo (needs avr-gcc)
2. flash the resulting hex-file on the microcontroller (I use avrdude with an AVRISP mkII)

