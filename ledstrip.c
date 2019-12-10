/*
 * Copyright (C) 2019 Marco Lochen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ledstrip.h"

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define DATA_LEN LED_COUNT * 3

static uint8_t data[DATA_LEN];
static uint8_t r, g, b;
static enum color_mode mode;

void ledstrip__init()
{
	DDRD |= 0x80;
}

void ledstrip__clear(void)
{
	for (uint16_t i = 0; i < DATA_LEN; i++)
	{
		data[i] = 0;
	}
}

void ledstrip__add(uint8_t n)
{
	for (uint16_t i = 0; i < DATA_LEN; i++)
	{
		if (UINT8_MAX - data[i] < n)
		{
			data[i] = UINT8_MAX;
		}
		else
		{
			data[i] += n;
		}
	}
}

void ledstrip__sub(uint8_t n)
{
	for (uint16_t i = 0; i < DATA_LEN; i++)
	{
		if (data[i] < n)
		{
			data[i] = 0;
		}
		else
		{
			data[i] -= n;
		}
	}
}

void ledstrip__set_color(uint8_t red, uint8_t green, uint8_t blue)
{
	r = red;
	g = green;
	b = blue;
}

void ledstrip__set_mode(enum color_mode color_mode)
{
	mode = color_mode;
}

void ledstrip__set_led(uint16_t led)
{
	if (led < LED_COUNT)
	{
		switch (mode)
		{
			case NORMAL:
				data[led * 3 + 0] = g;
				data[led * 3 + 1] = r;
				data[led * 3 + 2] = b;
				break;
			case ADD:
				data[led * 3 + 0] = (data[led * 3 + 0] + g > 255) ? 255 : (data[led * 3 + 0] + g);
				data[led * 3 + 1] = (data[led * 3 + 1] + r > 255) ? 255 : (data[led * 3 + 1] + r);
				data[led * 3 + 2] = (data[led * 3 + 2] + b > 255) ? 255 : (data[led * 3 + 2] + b);
				break;
			case SUBSTRACT:
				data[led * 3 + 0] -= g;
				data[led * 3 + 1] -= r;
				data[led * 3 + 2] -= b;
				break;
			case MULTIPLY:
				data[led * 3 + 0] *= g;
				data[led * 3 + 1] *= r;
				data[led * 3 + 2] *= b;
				break;
			case DIVIDE:
				data[led * 3 + 0] /= g;
				data[led * 3 + 1] /= r;
				data[led * 3 + 2] /= b;
				break;
		}
	}
}

void ledstrip__set_led_f(uint16_t led, double f)
{
	if (led < LED_COUNT)
	{
		switch (mode)
		{
			case NORMAL:
				data[led * 3 + 0] = g * f;
				data[led * 3 + 1] = r * f;
				data[led * 3 + 2] = b * f;
				break;
			case ADD:
				data[led * 3 + 0] = (data[led * 3 + 0] + g * f > 255) ? 255 : (data[led * 3 + 0] + g * f);
				data[led * 3 + 1] = (data[led * 3 + 1] + r * f > 255) ? 255 : (data[led * 3 + 1] + r * f);
				data[led * 3 + 2] = (data[led * 3 + 2] + b * f > 255) ? 255 : (data[led * 3 + 2] + b * f);
				break;
			case SUBSTRACT:
				data[led * 3 + 0] -= g * f;
				data[led * 3 + 1] -= r * f;
				data[led * 3 + 2] -= b * f;
				break;
			case MULTIPLY:
				data[led * 3 + 0] *= g * f;
				data[led * 3 + 1] *= r * f;
				data[led * 3 + 2] *= b * f;
				break;
			case DIVIDE:
				data[led * 3 + 0] /= g * f;
				data[led * 3 + 1] /= r * f;
				data[led * 3 + 2] /= b * f;
				break;
		}
	}
}

void ledstrip__show()
{
	cli();

	uint8_t *d = data;
	uint16_t len = DATA_LEN;

	asm volatile(
		"s_byte:\n"
		"ldi r18, 0x80\n" 		// maske initialisieren
		"ld r17, %a0+\n" 		// byte über pointer auslesen

		"pin_on:\n"
		"sbi %4, 7\n"

		"nop\n"
		"nop\n"
		"mov r16, r18\n"
		"and r16, r17\n" 		// wenn bit nicht gesetzt
		"breq pin_off\n" 		// ein paar nops überspringen
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"

		"pin_off:\n"
		"cbi %4, 7\n" 			// PORT D 7

		"mov r16, r18\n"
		"and r16, r17\n" 		// wenn bit gesetzt
		"brne re\n" 			// ein paar nops überspringen
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"re:\n"

		"lsr r18\n"
		"brne pin_on\n"
		
		"sbiw %a1, 1\n" 		// wenn len mal durchlaufen -> fertig
		"brne s_byte\n" 		// wenn nicht, dann weiter

		: "=x" (d), "=y" (len)
		: "0" (d), "1" (len), "I" (_SFR_IO_ADDR(PORTD))
		: "r16", "r17", "r18"
	);

	sei();

	_delay_us(60);
}
