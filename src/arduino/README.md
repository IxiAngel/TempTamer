# TempTamer Hardware Module

## About

The TempTamer Hardware Module complements the TempTamer Shell Script by providing fan speed control capabilities based on real-time
temperature readings. This module enables you to efficiently manage temperatures and fan speeds for optimal system performance and reliability.

To build and upload TempTamer, you will use one of these tools:

- Arduino IDE
- VSCode with PlatformIO

TempTamer is optimized to build with the PlatformIO IDE extension for Visual Studio Code. You can also build TempTamer using the Arduino IDE.

### Supported Boards

The following boards are currently supported by TempTamer:

- Arduino Uno
- Arduino Nano
- Arduino Mega
- ESP32
- ESP8266
- ...

## Quick Start

1. Download the GIT project and extract.
2. Using ![VSCode](https://code.visualstudio.com/download) and ![PlatformIO](https://platformio.org/install/ide?install=vscode) import `platformio.ini` project file.
3. Open PlatformIO.
4. Choose your board in project configuration under "Generic Options" Default is set to `wemos_d1_mini32`.
5. Connect the TempTamer Hardware Module (Arduino/ESP) to your computer via USB.
6. Ensure that the necessary Arduino serial drivers (FTDI, cp210x..) are installed, if required by your operating system.
7. Click PlatformIO: upload arrow or click `Project Tasks/General/Upload` button in the side platformIO menu.
8. Run ![tempTamer.sh](src/linux/tempTamer.sh) after reading the TempTamer Shell Script ![Readme](src/linux/README.md).

## Protocol and Interface

The TempTamer Hardware Module communicates with the system using a serial interface. It accepts commands in a specific format to adjust
fan speeds based on temperature readings received from the system.

### Command Format

```
{command,parameter1,parameter2,...}
```

### Commands

- `{0,fanIndex,fanSpeed}`: Sets speed of a single fan by fan index.
- `{1,fanBits=fanSpeed,...}`: Sets speed of multiple fans by fan bit index.
- `{2}`: Returns temperature from the temperature sensor.
- `{setConfig,optionName,value}`: Sets configuration option (tempSensorPin, tempSensorMaxTemp, tempSensorMaxTempFanSpeed, minFanSpeed).
- `{reset}`: Resets the fan controller.

Example:

```
{1,3=75}
```

This command sets the fan speed of the fans associated with the bit pattern `3` (first two fans) to 75%.

## Building from Source

If you prefer to build TempTamer Hardware Module from source:

1. Clone the TempTamer repository to your local machine.
2. Navigate to the `arduino/TempTamer` directory.
3. Open the `TempTamer.ino` file with Arduino Studio.
4. Edit the `config.h` file to configure TempTamer firmware. Adjust fan ports, initial fan speed, minimum fan speed, and temperature sensor settings as needed.
5. Select the correct board.
6. Press `Verify/Compile` or `Upload` to the board.
7. Once built, connect the hardware module to your computer and proceed with configuration and usage.

## Different Hardware Examples

TempTamer Hardware Module can be adapted to various hardware configurations and interfaces. ![Here](src/arduino/TempTamer_Circuit_Schematic.png) are some examples:

### Example 1: Arduino-based Module

- **Hardware**: Arduino Uno
- **Interface**: USB Serial
- **Components**: PWM-compatible fans, temperature probe (optional)
- **Configuration**: Upload the provided firmware to the Arduino Uno board.
- **Usage**: Connect fans and temperature probe to the Arduino, and control fan speeds using the serial interface. See [Schematic](src/arduino/TempTamer_Circuit_Schematic.png).

### Example 2: ESP32 HAT

- **Hardware**: ESP32/ESP-01
- **Interface**: USB Serial
- **Components**: PWM-compatible fans, temperature probe (optional)
- **Configuration**: Upload the provided firmware to the ESP board.
- **Usage**: Connect fans and temperature probe to the ESP, and control fan speeds using the serial interface.

### Example 3: TempTamer PCB HAT

- **Hardware**: Custom PCB with hat for Arduino/ESP
- **Interface**: USB Serial
- **Components**: PWM-compatible fans, temperature probe (optional)
- **Configuration**: Download and manufacture the PCB via JLC-PCB or similar, program the microcontroller.
- **Usage**: Connect fans, power, and temperature probe to the custom PCB HAT with Arduino or ESP32.


## Safety Considerations

**!!! WARNING: You are using this software at your own risk. Improperly configured or wired fan controller modules can damage your
hardware. Setting fan speeds too low can lead to overheating, which can also cause damage to your hardware. !!!**

To ensure safe operation:

- Ensure that the fan controller module is correctly connected and configured to avoid damaging hardware due to inadequate cooling.
- Use CAUTION when defining fan speed curves and temperature thresholds to prevent overheating and oscillations.
- Follow the safety principles or there will be problems!

## Contributions

Contributions to TempTamer are welcome!
Whether you're a seasoned developer or a newcomer, we appreciate all contributions that help improve TempTamer for the community.

## Support

For any questions, issues, or feedback, please open an issue on GitHub.

---
Copyright (c) 2024 TempTamer Developers
