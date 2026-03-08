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

#include "BuiltInRGB.h"
#include "Board.h"
#include "Arduino.h"
#include "FastLED.h"

#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void BuitlInRGB_init()
{
    FastLED.addLeds<NEOPIXEL, HUB_LED_PIN>(leds, NUM_LEDS); 
}

void BuitlInRGB_setColor(uint8_t r, uint8_t g, uint8_t b)
{
    leds[0].setRGB(r, g, b);
    FastLED.show();
}
