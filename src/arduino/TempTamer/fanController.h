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

#include "config.h"
#include "utils.h"

void setFanSpeed(int fanIndex, int percent)
{
	int value = (percent / 100.0) * 255;
#ifdef USE_LEDC
	ledcWrite(fanIndex, value);
#else
	analogWrite(FANS[fanIndex], percent);
#endif
}

void setMultiFanSpeed(long fanBits, int percent)
{
	for (int i = 0; i < sizeof(FANS) / sizeof(int); i++)
	{
		long bitMask = 1 << i;
		if (fanBits == 0 || (fanBits & bitMask) == bitMask)
		{
			setFanSpeed(i, percent);
		}
	}
}

void initFans(int percent)
{
	for (int i = 0; i < sizeof(FANS) / sizeof(int); i++)
	{
		pinMode(FANS[i], OUTPUT);
#ifdef USE_LEDC
		ledcSetup(i, 25000, 8);
		ledcAttachPin(FANS[i], i);
#endif
		setFanSpeed(i, percent);
	}
}

bool handleFanCommand(String data)
{
	String fanIndex = data.substring(data.indexOf(SPLIT_MARKER) + 1, data.lastIndexOf(SPLIT_MARKER));
	if (!isValidInteger(fanIndex))
	{
		return false;
	}

	int fanIndexInt = fanIndex.toInt();

	if (fanIndexInt < 0)
	{
		return false;
	}

	if (fanIndexInt > (sizeof(FANS) / sizeof(int)) - 1)
	{
		return false;
	}

	String fanSpeed = data.substring(data.lastIndexOf(SPLIT_MARKER) + 1);
	if (!isValidInteger(fanSpeed))
	{
		return false;
	}

	int fanSpeedInt = fanSpeed.toInt();

	if (fanSpeedInt < MIN_FAN_SPEED)
	{
		return false;
	}

	if (fanSpeedInt > 100)
	{
		return false;
	}

	setFanSpeed(fanIndexInt, fanSpeedInt);
	return true;
}

bool handleMultiFanCommand(String data)
{
	int startIndex = data.indexOf(SPLIT_MARKER) + 1;
  if (startIndex == 0)
  {
    return false;
  }

	while (startIndex != 0)
	{
		int endIndex = data.indexOf(SPLIT_MARKER, startIndex);
		String fanConfig = data.substring(startIndex, endIndex);
		startIndex = endIndex + 1;

		String fanBits = fanConfig.substring(0, fanConfig.indexOf("="));
		if (!isValidInteger(fanBits))
		{
			return false;
		}

		int fanBitsInt = fanBits.toInt();

		if (fanBitsInt < 0)
		{
			return false;
		}

		String fanSpeed = fanConfig.substring(fanConfig.indexOf("=") + 1);
		if (!isValidInteger(fanSpeed))
		{
			return false;
		}

		int fanSpeedInt = fanSpeed.toInt();

		if (fanSpeedInt < MIN_FAN_SPEED)
		{
			return false;
		}

		if (fanSpeedInt > 100)
		{
			return false;
		}

		setMultiFanSpeed(fanBitsInt, fanSpeedInt);
	}
	return true;
}
