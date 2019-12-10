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

#include "rainbow.h"
#include "../ledstrip.h"
#include "../column.h"

#include <math.h>
#include <stdlib.h>

#define DURATION 10
#define COLOR_DIST (LED_COUNT / 3.0f)

static uint8_t pa2color(uint16_t i, double p);

void rainbow__init(void)
{
}

void rainbow__update(double dt)
{
	static double offset = 0;
	offset += dt * (LED_COUNT / DURATION);
	if (offset >= LED_COUNT)
	{
		offset -= LED_COUNT;
	}

	ledstrip__clear();
	ledstrip__set_mode(NORMAL);
	
	for (uint16_t i = 0; i < LED_COUNT; i++)
	{
		double pos_r = fmod(offset, LED_COUNT);
		double pos_g = fmod(offset + COLOR_DIST, LED_COUNT);
		double pos_b = fmod(offset + COLOR_DIST * 2, LED_COUNT);

		uint8_t r = pa2color(i, pos_r);
		uint8_t g = pa2color(i, pos_g);
		uint8_t b = pa2color(i, pos_b);

		ledstrip__set_color(r, g, b);
		ledstrip__set_led(i);
	}

	ledstrip__show();
}

static uint8_t pa2color(uint16_t i, double p)
{
	double dist = fabs(i - p);
	dist = (dist > (LED_COUNT / 2)) ? LED_COUNT - dist : dist;
	return (dist > COLOR_DIST) ? 0 : 255 - (uint8_t)(dist * (255 / COLOR_DIST));
}

