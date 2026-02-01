//? ------------------------------------------------------------------------------------------
//*! This file contains all the hardware pinout definitions for the project.
//? ------------------------------------------------------------------------------------------

#ifndef PROJECT_GLOBAL_PINOUT
#define PROJECT_GLOBAL_PINOUT

#include "shared/dependencies.h"

//* Inputs:
#define main_detect_pin 12

//* Outputs:
#define open_drain_pin 13
#define triac_pin 14
#define LED_pin 4

//* 1Wire Bus:
#define one_wire_pin 16

//* PORT1 (Serial0):
#define tx_0 1
#define rx_0 3

//* I2C pins:
#define i2c_sda 21
#define i2c_scl 22

#define prog_switch GPIO_NUM_0 // GPIO0 is used for programming mode detection

#endif // PROJECT_GLOBAL_PINOUT
