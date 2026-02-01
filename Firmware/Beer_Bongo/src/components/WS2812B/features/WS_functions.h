#if !defined(START_BREATHING_EFFECT_LEDS)
#define START_BREATHING_EFFECT_LEDS

#define redLED 0xFF, 0x0, 0x0
#define greenLED 0x0, 0xFF, 0x0
#define blueLED 0x0, 0x0, 0xFF

#include "shared/dependencies.h"

void blink_pixel(uint8_t color, uint8_t times, uint16_t delayTime);
void soft_pulse();
void light_pixel();

void blink_pixel(uint8_t color, uint8_t times, uint16_t delayTime)
{
    uint8_t red = (color & 0x1) ? 100 : 0;
    uint8_t green = (color & 0x2) ? 100 : 0;
    uint8_t blue = (color & 0x4) ? 100 : 0;
    for (int j = 0; j < times * 2; j++)
    {
        for (int i = 0; i < ONBOARD_LEDS; i++)
        {
            onboard_pixel.setPixelColor(i, onboard_pixel.Color(red * ((j + 1) % 2), green * ((j + 1) % 2), blue * ((j + 1) % 2)));
        }
        onboard_pixel.show();
        delay(delayTime);
    }
}

void soft_pulse()
{
    float sin1 = sin(((millis() * (2 * PI)) / 2000.0));
    sin1 *= sin1; // Square the sine wave for a sharper effect
    sin1 *= sin1; // Square it again
    onboard_led.brightness = 50 * (sin1 > 0 ? sin1 : 0);
    onboard_led.color = 0x4; // Blue color
    for (int i = 0; i < ONBOARD_LEDS; i++)
        onboard_pixel.setPixelColor(i, onboard_pixel.Color(0, 0, onboard_led.brightness));

    onboard_pixel.show();
}

void light_pixel()
{
    float brightness = 25;
    // brightness = sin(((millis() * (2 * PI)) / 1500.0)) * 30 + 50;
    onboard_led.brightness = constrain(brightness, 0, 150);
    onboard_led.color = millis() / 1000 % 7 + 1; // Change color every 1500ms
    bool hasRed = onboard_led.color & 0x1;
    bool hasGreen = onboard_led.color & 0x2;
    bool hasBlue = onboard_led.color & 0x4;
    uint8_t numColors = hasRed + hasGreen + hasBlue; // Normalizes intensity based on number of active colors
    onboard_led.red = hasRed ? onboard_led.brightness / numColors : 0;
    onboard_led.green = hasGreen ? onboard_led.brightness / numColors : 0;
    onboard_led.blue = hasBlue ? onboard_led.brightness / numColors : 0;
    uint8_t fade = 15;

    onboard_led.index = millis() / 300 % ONBOARD_LEDS + ONBOARD_LEDS; // Tagets a pixel between 0 and ONBOARD_LEDS every 150ms, plus offset

    onboard_pixel.setPixelColor(onboard_led.index % ONBOARD_LEDS, onboard_pixel.Color(onboard_led.red, onboard_led.green, onboard_led.blue));
    onboard_pixel.setPixelColor((onboard_led.index - 1) % ONBOARD_LEDS, onboard_pixel.Color(onboard_led.red / fade, onboard_led.green / fade, onboard_led.blue / fade));
    onboard_pixel.setPixelColor((onboard_led.index - 2) % ONBOARD_LEDS, onboard_pixel.Color(0, 0, 0));

    onboard_pixel.show(); // update to the WS2812B Led Strip
}

#endif // START_BREATHING_EFFECT_LEDS
