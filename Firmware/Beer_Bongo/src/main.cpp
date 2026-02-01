#include "shared/dependencies.h"

void update_rgb_values(uint8_t colorCode);

void setup()
{
  //* --- SERIAL BEGIN ---
  //* Begin serial communication with Serial Monitor.
  Serial.begin(115200);

  Serial.println("\n---------------------------------------------------");
  Serial.println("------------------ Void Setup  --------------------");
  Serial.println("---------------------------------------------------\n");

  setup_ESP32();   //* Enables WiFi modem, disables BLE, enables watchdog
  setup_DISPLAY(); //* Enables debug display
  setup_WS2812B(); //* Enables debug WS2812B LED
  setup_WIFI();    //* Setups AP for control
  // WiFi.mode(WIFI_OFF); //* Disable WiFi for lower power consumption
  setup_WEBSERVER(); //* Setup webserver

  Serial.println("\n---------------------------------------------------");
  Serial.println("----------------  END OF SETUP --------------------");
  Serial.println("---------------------------------------------------\n");
  esp_task_wdt_reset();
}

void loop()
{
  ArduinoOTA.handle();
  serial_outputs();
  soft_pulse();
  check_power_button();
  webserver_handle();
  check_mains_frequency();
  analogWrite(open_drain_pin, 255 - PWM_output); // Set PWM output value

  esp_task_wdt_reset();
}
