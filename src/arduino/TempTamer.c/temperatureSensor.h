// Copyright (C) 2024 IxiAngel
//
// TempTamer Fan Controller Module is free software: you can redistribute it and/or modify
// it under the terms of the MIT License as published
// by the Open Source Initiative.
//
// TempTamer Fan Controller Module is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// MIT License for more details.

OneWire* oneWire = NULL;
DallasTemperature* dallasTemperature = NULL;

void initTemperatureSensor(int oneWirePin)
{
	pinMode(oneWirePin, OUTPUT);
	oneWire = new OneWire(oneWirePin);
	dallasTemperature = new DallasTemperature(oneWire);
}

float getTemperature()
{
  dallasTemperature->requestTemperatures();
  return dallasTemperature->getTempCByIndex(0);
}
