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

#include "beacon.h"
#include "../ledstrip.h"
#include "../column.h"

void beacon__init(void)
{
}

void beacon__update(double dt)
{
    static double t = 0;
    t += dt * 2;
    if (t >= 1)
    {
        t -= 1;
    }

    ledstrip__clear();
    ledstrip__set_mode(NORMAL);

    ledstrip__set_color(0, 0, 255);
    column__vbar(t * 360, 120, 30);

    ledstrip__show();
}

