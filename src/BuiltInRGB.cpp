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
