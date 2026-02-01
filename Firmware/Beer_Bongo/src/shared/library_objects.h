#if !defined(PROJECT_GLOBAL_OBJECTS)
#define PROJECT_GLOBAL_OBJECTS

#include "shared/dependencies.h"
#include "pinout.h"

//* ---------------------- GLOBAL OBJECT INSTANCES ----------------------

//* 0.96" OLED I2C display
Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define ONBOARD_LEDS 1

//* Fancy LED WS2812B
Adafruit_NeoPixel onboard_pixel(ONBOARD_LEDS, LED_pin, NEO_GRB + NEO_KHZ800); // Embeddeed WS2812B ring on devkit board

//* Preferences (NVS)
Preferences preferences;

#endif // PROJECT_GLOBAL_OBJECTS
