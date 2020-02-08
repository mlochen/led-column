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

#include "colorwave.h"
#include "../ledstrip.h"
#include "../column.h"

#include <math.h>
#include <stdlib.h>


void colorwave__init(void)
{
}

void colorwave__update(double dt)
{
    static double t = 0;
    t += dt;
    if (t >= M_PI)
    {
        t -= M_PI;
    }

    double sint = (sin(t * 2) + 1) / 2;

    ledstrip__clear();
    ledstrip__set_mode(NORMAL);
    ledstrip__set_color(0, 255 * sint, 255 - 255 * sint);
    column__ring(sint * LED_COUNT, LED_COUNT / 2, LED_COUNT / 10);
    ledstrip__show();
}

