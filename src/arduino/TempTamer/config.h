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

//ESP detection for keeping the pin naming scheme cross-platform and usage of LEDC that Arduino AVR does not support.
#include "platform.h"

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