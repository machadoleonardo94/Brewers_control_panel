#if !defined(SERVICE_INPUT_READINGS)
#define SERVICE_INPUT_READINGS

#include "shared/dependencies.h"

void check_mains_frequency()
{
    // Handle main detect pin interrupt
    static uint32_t last_time = 0;
    if ((millis() - last_time) > 10000)
    {

        mains_frequency = main_detect_count / 40.0;
        Serial.printf("Mains Frequency: %.2f Hz\n", mains_frequency);
        main_detect_count = 0;
        last_time = millis();
    }
}

#endif