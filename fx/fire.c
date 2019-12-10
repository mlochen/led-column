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

#include "fire.h"
#include "../ledstrip.h"
#include "../column.h"

#include <stdlib.h>

void fire__init(void)
{
}

void fire__update(double dt)
{
	ledstrip__clear();
	ledstrip__set_mode(ADD);

	double brightness = 0.7f + 0.3f * ((double)rand() / RAND_MAX);
	uint16_t size;

	size = 400 * brightness;
	ledstrip__set_color(192, 32, 0);
	column__ring(30, size, size / 2);

	size = 180 * brightness;
	ledstrip__set_color(255, 255, 0);
	column__ring(30, size, size / 2);

	size = 60 * brightness;
	ledstrip__set_color(255, 255, 255);
	column__ring(30, size, size / 2);

	ledstrip__show();
}

