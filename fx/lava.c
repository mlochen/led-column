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

#include "lava.h"
#include "../ledstrip.h"
#include "../column.h"

#include <stdlib.h>
#include <math.h>

#define BALL_COUNT 6

struct lava_ball {
	uint16_t size;
	double t;
	uint8_t r, g, b;
};

static struct lava_ball ball[BALL_COUNT];

void lava__init(void)
{
	for (uint8_t i = 0; i < BALL_COUNT; i++)
	{
		ball[i].size = (rand() % 50) + 60;
		ball[i].t = (rand() % 314) / 100.0f;
		uint8_t rgb = 0xB2 >> i;
		ball[i].r = ((rgb & 4) >> 2) * 255;
		ball[i].g = ((rgb & 2) >> 1) * 255;
		ball[i].b = ((rgb & 1) >> 0) * 255;
	}
}

void lava__update(double dt)
{
	ledstrip__clear();
	ledstrip__set_mode(ADD);

	for (uint8_t i = 0; i < BALL_COUNT; i++)
	{
		ball[i].t += dt * 4 / ball[i].size;
		if (ball[i].t > M_PI)
		{
			ball[i].t -= M_PI;
		}
		double pos = (sin(ball[i].t * 2) + 1) / 2;
		ledstrip__set_color(ball[i].r, ball[i].g, ball[i].b);
		column__ring(pos * LED_COUNT, ball[i].size, 10);
	}

	ledstrip__show();
}

