// Copyright (C) 2024 TempTamer Developers
//
// TempTamer Fan Controller Module is free software: you can redistribute it and/or modify
// it under the terms of the MIT License as published
// by the Open Source Initiative.
//
// TempTamer Fan Controller Module is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// MIT License for more details.

#ifndef __CONFIG_H__
#define __CONFIG_H__


//ESP32 to Arduino naming pin defines. 
#ifndef CONFIG_IDF_TARGET_ESP32
typedef enum {
    GPIO_NUM_0 = 0,     /*!< GPIO0, input and output */
    GPIO_NUM_1 = 1,     /*!< GPIO1, input and output */
    GPIO_NUM_2 = 2,     /*!< GPIO2, input and output */
    GPIO_NUM_3 = 3,     /*!< GPIO3, input and output */
    GPIO_NUM_4 = 4,     /*!< GPIO4, input and output */
    GPIO_NUM_5 = 5,     /*!< GPIO5, input and output */
    GPIO_NUM_6 = 6,     /*!< GPIO6, input and output */
    GPIO_NUM_7 = 7,     /*!< GPIO7, input and output */
    GPIO_NUM_8 = 8,     /*!< GPIO8, input and output */
    GPIO_NUM_9 = 9,     /*!< GPIO9, input and output */
    GPIO_NUM_10 = 10,   /*!< GPIO10, input and output */
    GPIO_NUM_11 = 11,   /*!< GPIO11, input and output */
    GPIO_NUM_12 = 12,   /*!< GPIO12, input and output */
    GPIO_NUM_13 = 13,   /*!< GPIO13, input and output */
    GPIO_NUM_14 = 14,   /*!< GPIO14, input and output */
    GPIO_NUM_15 = 15,   /*!< GPIO15, input and output */
    GPIO_NUM_16 = 16,   /*!< GPIO16, input and output */
    GPIO_NUM_17 = 17,   /*!< GPIO17, input and output */
    GPIO_NUM_18 = 18,   /*!< GPIO18, input and output */
    GPIO_NUM_19 = 19,   /*!< GPIO19, input and output */
    GPIO_NUM_20 = 20,   /*!< GPIO20, input and output */
    GPIO_NUM_21 = 21,   /*!< GPIO21, input and output */
    GPIO_NUM_22 = 22,   /*!< GPIO22, input and output */
    GPIO_NUM_MAX,
/** @endcond */
} gpio_num_t;
#endif

//Only ESP supports LEDC. Disable if building for Arduino AVR targets.
//#define USE_LEDC

// Fan ports and number of fans to use.
const int FANS[6] = { GPIO_NUM_19, GPIO_NUM_18, GPIO_NUM_5, GPIO_NUM_17, GPIO_NUM_16, GPIO_NUM_4 };

// Initial fan speed.
const int INITIAL_FAN_SPEED = 50;

// Minimum fan speed - prevent setting fans below this speed.
int MIN_FAN_SPEED = 10;

// Set all fans to maximum if no data is received for specified seconds.
int EMERGENCY_TIMEOUT = 60;

// (Optional) Temperature sensor port. Use -1 to disable.
// OneWire/DallasTemperature (i.e. DS18B20) is supported.
int TEMP_SENSOR_PIN = -1;
// (Optional) Set fans to max speed if temperature of the sensor drops to specified value or below in Celsius.
const int TEMP_SENSOR_MIN_TEMP = 0;
// (Optional) Set fans to TEMP_SENSOR_MAX_TEMP_FAN_SPEED speed if temperature of the sensor reaches or is higher than the specified value in Celsius.
int TEMP_SENSOR_MAX_TEMP = 80;
// (Optional) Set fans to below speed if temperature of the sensor reaches or is higher than the TEMP_SENSOR_MAX_TEMP value.
int TEMP_SENSOR_MAX_TEMP_FAN_SPEED = 90;

#endif