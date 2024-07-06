# TempTamer Hardware Module

## About

The TempTamer Hardware Module complements the TempTamer Shell Script, providing fan speed control capabilities based on real-time temperature readings.
With this module, you can efficiently manage CPU temperatures and fan speeds for optimal system performance and reliability.

To build and upload TempTamer you will use one of these tools:

    -Arduino IDE
    -VSCode with PlatformioIO

TempTamer is optimized to build with the PlatformIO IDE extension for Visual Studio Code. You can still build TempTamer with Arduino IDE.

## Quick Prep/Start from Pre-built Binaries

1. Download the pre-built binaries for your platform from the TempTamer GitHub releases page.
2. Connect the TempTamer Hardware Module to your computer via the appropriate interface (e.g. USB).
3. Ensure that the necessary drivers are installed, if required by your operating system.
4. Run the executable file to start using TempTamer immediately.

## Protocol/Interface

The TempTamer Hardware Module communicates with the system using a serial interface.
It accepts commands in a specific format to adjust fan speeds based on temperature readings received from the system.

### Command Format:

```
{command,parameter1,parameter2,...}
```

### Commands

- `{0,fanIndex,fanSpeed}`: Sets speed of a single fan.
- `{1,fanBits=fanSpeed,...}`: Sets speed of multiple fans.
- `{2}`: Returns temperature from temperature sensor.
- `{setConfig,optionName,value}`: Sets configuration option (tempSensorPin, tempSensorMaxTemp, tempSensorMaxTempFanSpeed, minFanSpeed).
- `{reset}`: Resets the fan controller.

Example:
```
{1,3=75}
```

This command sets the fan speed of the fans associated with the bit pattern `3 (11b)` to 75%.

## Build from Source

If you prefer to build TempTamer Hardware Module from source:
1. Clone the TempTamer repository to your local machine.
2. Navigate to the `arduino/TempTamer` directory.
3. Open `TempTamer.ino` file with Arduino Studio.
4. Edit `config.h` file, to configure TempTamer firmware. Adjust fan ports, initial fan speed, minimum fan speed, and temperature sensor settings as needed.
5. Select the correct Board.
6. Press `Verify/Compile` or `Upload` to the board.
7. Once built, connect the hardware module to your computer and proceed with configuration and usage.


## Different Hardware Examples

TempTamer Hardware Module can be adapted to various hardware configurations and interfaces. Here are some examples:

### Example 1: Arduino-based Module

- **Hardware**: Arduino Uno
- **Interface**: USB Serial
- **Components**: PWM-compatible fans, temperature probe (optional)
- **Configuration**: Upload the provided firmware to the Arduino Uno board.
- **Usage**: Connect fans and temperature probe to the Arduino, and control fan speeds using the serial interface.

### Example 2: ESP32 HAT

- **Hardware**: ESP32/ESP-01
- **Interface**: USB Serial
- **Components**: PWM-compatible fans, temperature probe (optional)
- **Configuration**: Upload the provided firmware to the ESP board.
- **Usage**: Connect fans and temperature probe to the ESP, and control fan speeds using the serial interface.

### Example 3: TempTamer PCB HAT

- **Hardware**: Custom PCB with hat for arduino/esp
- **Interface**: USB Serial
- **Components**: PWM-compatible fans, temperature probe (optional)
- **Configuration**: Download and manufacture the PCB via JLC-PCB or similar, program the microcontroller.
- **Usage**: Connect fans, power and temperature probe to the custom PCB HAT with Arduino or ESP32. 

## Safety Considerations

**!!! You are using this software at your own risk. You can damage your hardware if the module is wired or configured incorrectly or if fan speeds are set too low. !!!**

- Ensure that the fan controller module is correctly connected and configured to avoid damaging hardware due to inadequate cooling.
- Use CAUTION when defining fan speed curves and temperature thresholds to prevent overheating and oscillations.
- Follow the safety principles or there will be problems!

## Contributions

Contributions to TempTamer are welcome!
Whether you're a seasoned developer or a newcomer, we appreciate all contributions that help improve TempTamer for the community.

## Support

For any questions, issues, or feedback, please open an issue on GitHub.
