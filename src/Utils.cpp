/**
 *  Copyright (C) 2026 - Rbel12b
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  */

#include "Utils.h"
#include "Arduino.h"

unsigned long util_panStartTime = 0;

int panValue()
{
    const unsigned long halfPeriod = 3000; // 3 seconds
    const unsigned long fullPeriod = 6000; // 6 seconds

    unsigned long now = millis();
    unsigned long t = (now - util_panStartTime) % fullPeriod;

    if (t < halfPeriod)
    {
        // 0 -> 180
        return map(t, 0l, halfPeriod, 0l, 180l);
    }
    else
    {
        // 180 -> 0
        return map(t - halfPeriod, 0l, halfPeriod, 180l, 0l);
    }
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}