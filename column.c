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

#include "column.h"

#include <math.h>
#include <stdlib.h>
#include "ledstrip.h"

#define LEDS_PER_REV (300 / 30.6f)

void column__ring(double pos, uint16_t height, uint16_t fade)
{
	double fade_dist = ((double)height / 2) - fade;
	int16_t start = ceil(pos - ((double)height / 2));
	int16_t end = floor(pos + ((double)height / 2));

	for (int16_t i = start; i <= end; i++)
	{
		double dist = fabs(pos - i);
		if (dist <= fade_dist)
		{
			ledstrip__set_led(i);
		}
		else
		{
			double factor = (fade - (dist - fade_dist)) / fade;
			ledstrip__set_led_f(i, factor);
		}
	}
}

void column__vbar(int16_t angle, uint16_t width, uint16_t fade)
{
	for (uint16_t i = 0; i < LED_COUNT; i++)
	{
		double fade_dist = ((double)width / 2) - fade;
		int16_t led_angle = modf(i / LEDS_PER_REV, NULL) * 360;
		
		uint16_t dist = abs(angle - led_angle);
		dist = (dist > 180) ? 360 - dist : dist;

		if (dist <= fade_dist)
		{
			ledstrip__set_led(i);
		}
		else if (dist < (width / 2))
		{
			double factor = (double)((width / 2) - dist) / fade;
			ledstrip__set_led_f(i, factor);
		}
	}
}
