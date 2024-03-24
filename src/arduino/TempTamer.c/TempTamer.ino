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

#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
#include "utils.h"
#include "fanController.h"
#include "temperatureSensor.h"

#define LOOP_INTERVAL_MS 5

boolean ledEnabled = false;

const String INIT_MESSAGE = "TempTamer Fan Controller Module v1.0";

// Command related strings

const String CMD_RESET = "reset";
const String CMD_SET_CONFIG = "setConfig";
const String CMD_FAN = "0";
const String CMD_MULTI_FAN = "1";
const String CMD_GET_TEMPERATURE = "2";
const String CMD_PING = "ping";

const String CMD_OK = "OK";

const String CMD_UNKNOWN = "ERR: Unknown command.";
const String CMD_FAN_ERROR = "ERR: Error processing fan command.";
const String CMD_SET_CONFIG_ERROR = "ERR: Error processing setConfig command.";

const String CMD_TEMP_SENSOR_NOT_ENABLED = "ERR: Temperature sensor not enabled.";

long lastDataReceived = millis();
long lastTemperatureCheck = 0;

void initBuiltInLed()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
}

void setup()
{
	initBuiltInLed();
	Serial.begin(115200);

	Serial.println();
	Serial.println(INIT_MESSAGE);

	Serial.printf("Initial Fan Speed: %i, Min Fan Speed: %i, Temp Sensor Pin: %i, Temp Sensor Min: %i, Temp Sensor Max: %i.",
		INITIAL_FAN_SPEED,
		MIN_FAN_SPEED,
		TEMP_SENSOR_PIN,
		TEMP_SENSOR_MIN_TEMP,
		TEMP_SENSOR_MAX_TEMP);
	Serial.println();

#ifdef USE_LEDC
	Serial.println("Info: Using ledcWrite(...).");
#else
	Serial.println("Warning: Using analogWrite(...). Please use \"#define USE_LEDC\" where possible.");
#endif

	help();

	initFans(INITIAL_FAN_SPEED);
	if (TEMP_SENSOR_PIN != -1)
	{
		initTemperatureSensor(TEMP_SENSOR_PIN);
	}
}

void help()
{
	Serial.println("Example usage: \"{command,param1,param2,...}\".");
	Serial.println("Commands:");
	Serial.println(" {0,fanIndex,fanSpeed} - Sets speed of a single fan.");
	Serial.println(" {1,fanBits} - Sets speed of multiple fans.");
	Serial.println(" {2} - Returns temperature from sensor.");
	Serial.println(" {setConfig,optionName,value} - Sets configuration option (tempSensorPin, tempSensorMaxTemp, tempSensorMaxTempFanSpeed, minFanSpeed).");
	Serial.println(" {reset} - Resets the fan controller.");
}

boolean handleSetConfig(String data)
{
	String configOption = data.substring(data.indexOf(SPLIT_MARKER) + 1, data.lastIndexOf(SPLIT_MARKER));

	if (configOption == "tempSensorPin")
	{
		String pin = data.substring(data.lastIndexOf(SPLIT_MARKER) + 1);
		if (!isValidInteger(pin))
		{
			return false;
		}

		int pinInt = pin.toInt();
		if (pinInt != TEMP_SENSOR_PIN)
		{
			TEMP_SENSOR_PIN = pinInt;
			if (TEMP_SENSOR_PIN != -1)
			{
				initTemperatureSensor(TEMP_SENSOR_PIN);
			}
		}
		return true;
	}
	else if (configOption == "tempSensorMaxTemp")
	{
		String maxTemp = data.substring(data.lastIndexOf(SPLIT_MARKER) + 1);
		if (!isValidInteger(maxTemp))
		{
			return false;
		}

		int maxTempInt = maxTemp.toInt();
		if (maxTempInt != TEMP_SENSOR_MAX_TEMP)
		{
			TEMP_SENSOR_MAX_TEMP = maxTempInt;
		}
		return true;
	}
	else if (configOption == "tempSensorMaxTempFanSpeed")
	{
		String fanSpeed = data.substring(data.lastIndexOf(SPLIT_MARKER) + 1);
		if (!isValidInteger(fanSpeed))
		{
			return false;
		}

		int fanSpeedInt = fanSpeed.toInt();
		if (fanSpeedInt != TEMP_SENSOR_MAX_TEMP_FAN_SPEED)
		{
			TEMP_SENSOR_MAX_TEMP_FAN_SPEED = fanSpeedInt;
		}
		return true;
	}
	else if (configOption == "minFanSpeed")
	{
		String minFanSpeed = data.substring(data.lastIndexOf(SPLIT_MARKER) + 1);
		if (!isValidInteger(minFanSpeed))
		{
			return false;
		}

		int minFanSpeedInt = minFanSpeed.toInt();
		if (minFanSpeedInt != MIN_FAN_SPEED)
		{
			MIN_FAN_SPEED = minFanSpeedInt;
		}
		return true;
	}
	else if (configOption == "emergencyTimeout")
	{
		String emergencyTimeout = data.substring(data.lastIndexOf(SPLIT_MARKER) + 1);
		if (!isValidInteger(emergencyTimeout))
		{
			return false;
		}

		EMERGENCY_TIMEOUT = emergencyTimeout.toInt();
		return true;
	}

	return false;
}

void processData(String data)
{
	if (data == "")
	{
		return;
	}

	String command = "";
	if (data.indexOf(SPLIT_MARKER) != -1)
	{
		command = data.substring(0, data.indexOf(SPLIT_MARKER));
	}
	else
	{
		command = data;
	}

	if (command == CMD_RESET)
	{
		ESP.restart();
	}
	else if (command == CMD_FAN)
	{
		if (handleFanCommand(data))
		{
			lastDataReceived = millis();
			Serial.println(CMD_OK);
		}
		else
		{
			Serial.println(CMD_FAN_ERROR);
		}
	}
	else if (command == CMD_MULTI_FAN)
	{
		if (handleMultiFanCommand(data))
		{
			lastDataReceived = millis();
			Serial.println(CMD_OK);
		}
		else
		{
			Serial.println(CMD_FAN_ERROR);
		}
	}
	else if (command == CMD_PING)
	{
		lastDataReceived = millis();
		Serial.println(CMD_OK);
	}
	else if (command == CMD_GET_TEMPERATURE)
	{
		if (dallasTemperature != NULL)
		{
			Serial.println(dallasTemperature->getTempCByIndex(0));
		}
		else
		{
			Serial.println(CMD_TEMP_SENSOR_NOT_ENABLED);
		}
	}
	else if (command == CMD_SET_CONFIG)
	{
		if (handleSetConfig(data))
		{
			Serial.println(CMD_OK);
		}
		else
		{
			Serial.println(CMD_SET_CONFIG_ERROR);
		}
	}
	else
	{
		Serial.println(CMD_UNKNOWN);
	}
}

void checkTemperature()
{
	if (TEMP_SENSOR_PIN == -1)
	{
		return;
	}

	if (millis() - lastTemperatureCheck > 100)
	{
		lastTemperatureCheck = millis();
		float temp = getTemperature();
		if (temp <= TEMP_SENSOR_MIN_TEMP
			|| temp >= TEMP_SENSOR_MAX_TEMP)
		{
			setMultiFanSpeed(0, TEMP_SENSOR_MAX_TEMP_FAN_SPEED);
		}
	}
}

void loop()
{
	String data = readSerialData();
	processData(data);

	if (data == "")
	{
		// Delay and check temperature only if no data is being received.
		delay(LOOP_INTERVAL_MS);
		checkTemperature();

		// If no data received for over EMERGENCY_TIMEOUT seconds, set all fans to max.
		if (EMERGENCY_TIMEOUT > 0 && millis() - lastDataReceived > EMERGENCY_TIMEOUT * 1000)
		{
			setMultiFanSpeed(0, TEMP_SENSOR_MAX_TEMP_FAN_SPEED);
			lastDataReceived = millis();
		}
	}

	ledEnabled = !ledEnabled;
	digitalWrite(LED_BUILTIN, ledEnabled);
}
