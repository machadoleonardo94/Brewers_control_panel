#if !defined(SETUP_ESP32)
#define SETUP_ESP32

#include "shared/dependencies.h"
#include "components/ESP32/features/update_firmware_ota.h"

// ISR for main detect pin. Increments a counter and sets a flag for main loop to handle.
void IRAM_ATTR main_detect_isr()
{
    main_detect_triggered = true;
    main_detect_count++;
}

void setup_ESP32()
{
    Serial.println("[ESP32] SETUP STARTED!");

    //* Setup bluetooth
    btStop();

    //* Setup Watchdog
    esp_task_wdt_init(180, true);
    esp_task_wdt_add(NULL);

    WiFi.mode(WIFI_AP_STA);

    //* Configures INPUTS
    pinMode(prog_switch, INPUT);
    pinMode(main_detect_pin, INPUT_PULLUP);
    // Attach interrupt to detect changes on main_detect_pin
    attachInterrupt(digitalPinToInterrupt(main_detect_pin), main_detect_isr, CHANGE);

    //* Configure OUTPUT pins
    pinMode(triac_pin, OUTPUT);
    pinMode(open_drain_pin, OUTPUT);
    digitalWrite(triac_pin, LOW);
    digitalWrite(open_drain_pin, HIGH);

    esp_sleep_enable_ext0_wakeup(prog_switch, LOW);

    setup_OTA();

    Serial.println("[ESP32] SETUP FINISHED!");
}

#endif // SETUP_ESP32