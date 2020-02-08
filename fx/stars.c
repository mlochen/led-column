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

#include "stars.h"
#include "../ledstrip.h"

#include <stdlib.h>

#define STAR_RATE 50
#define FADE_TIME 2

void stars__init(void)
{
}

void stars__update(double dt)
{
    static double t = 0;
    t += dt;

    ledstrip__sub(255 * dt / FADE_TIME);
    ledstrip__set_mode(NORMAL);

    while(t > (1.0f / STAR_RATE))
    {
        ledstrip__set_color(rand() % 256, rand() % 256, rand() % 256);
        ledstrip__set_led(rand() % LED_COUNT);
        t -= (1.0f / STAR_RATE);
    }
    ledstrip__show();
}

