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

#ifndef __LEDSTRIP_H__
#define __LEDSTRIP_H__

#include <stdint.h>

#define LED_COUNT 300

enum color_mode {
    NORMAL,
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE
};

void ledstrip__init(void);
void ledstrip__clear(void);
void ledstrip__add(uint8_t n);
void ledstrip__sub(uint8_t n);
void ledstrip__set_color(uint8_t red, uint8_t green, uint8_t blue);
void ledstrip__set_mode(enum color_mode color_mode);
void ledstrip__set_led(uint16_t led);
void ledstrip__set_led_f(uint16_t led, double f);
void ledstrip__show(void);

#endif
