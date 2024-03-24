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

#ifndef __UTILS_H__
#define __UTILS_H__

// Protocol related markers
#define START_MARKER '{'
#define END_MARKER '}'
#define SPLIT_MARKER ","

String readSerialData(int maxLength = 100)
{
	// Wait in total 100ms (100 iterations with 1ms delay) for data in case of slow transfers.
	unsigned long totalDelayTimeoutMs = 100;

	// Wait in total 500ms for start marker when other data is being received.
	unsigned long startMarkerTimeoutMs = 500;

	String data = "";
	unsigned long startTime = millis();
	unsigned long totalDelayIterator = 0;

	boolean error = false;
	while (Serial.available())
	{
		char c = Serial.read();

		if (data.length() == 0
			&& c != START_MARKER)
		{
			error = true;
			if (millis() - startTime > startMarkerTimeoutMs)
			{
				break;
			}
			continue;
		}

		if (c == END_MARKER)
		{
			// Remove start marker
			return data.substring(1);
		}

		data += c;

		// No command is longer than maxLength bytes, so if no end marker within maxLength bytes, discard the data.
		if (data.length() > maxLength)
		{
			error = true;
			break;
		}

		for (; totalDelayIterator < totalDelayTimeoutMs && !Serial.available(); totalDelayIterator++)
		{
			delay(1);
		}
	}

	return "";
}

boolean isValidInteger(String str)
{
	if (str == NULL || str.length() == 0)
	{
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (!isDigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

#endif