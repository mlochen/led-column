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
#include "fx/beacon.h"
#include "fx/colorwave.h"
#include "fx/fire.h"
#include "fx/lava.h"
#include "fx/rainbow.h"
#include "fx/stars.h"

#include <avr/io.h>

int main()
{
	ledstrip__init();

	beacon__init();
	colorwave__init();
	fire__init();
	lava__init();
	rainbow__init();
	stars__init();

	TCCR1B = (1 << CS12) | (1 << CS10);

	while(1)
	{
		static double t = 0;
		double dt = TCNT1 / 15625.0f;
		TCNT1 = 0;
		t += dt;
		if (t >= 60)
		{
			t = 0;
		}

		switch ((uint8_t)(t / 10))
		{
			case 0: beacon__update(dt); break;
			case 1: colorwave__update(dt); break;
			case 2: fire__update(dt); break;
			case 3: lava__update(dt); break;
			case 4: rainbow__update(dt); break;
			case 5: stars__update(dt); break;
		}
	}
}
