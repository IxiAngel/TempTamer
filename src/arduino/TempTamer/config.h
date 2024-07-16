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

//Only ESP supports LEDC. Disable if building for Arduino AVR targets.
#define USE_LEDC

//Only ESP supports software reset. (Arduino supports only jumping to addr 0)
//#define ESP32

// Fan ports to use.
const int FANS[6] = { 2, 3, 4, 6, 8, 9 };

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