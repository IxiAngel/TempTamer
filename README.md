# TempTamer: The Cool CPU Commander

## About

TempTamer is the ultimate solution for limiting CPU clock speed and fan speeds with finesse, ensuring optimal performance while
keeping temperatures and CPU stability in check. This tool consists of two modules:

- A TempTamer bash script for Linux systems which reads CPU temperature, limits CPU frequencies as configured by the user, and
interfaces with the TempTamer Hardware Module to control fan speed.
- The TempTamer Hardware Module for controlling fan speeds.

## Requirements

To use TempTamer, you'll need:
- Compatible computer with CPU temperature monitoring capabilities
- PWM-compatible fans
- Dallas DS18B20 temperature probe (optional)
- ESP32 microcontroller or Arduino board

## Configuring and Starting the TempTamer Shell Script on Linux

1. Clone the TempTamer repository to your computer.
2. Navigate to the directory containing the bash script.
3. Make the script executable using the command: `chmod +x tempTamer.sh`.
4. Create a configuration file and configure temperature thresholds and fan speed curves according to your requirements.
5. Run the script using the command: `./tempTamer.sh`.

The script continuously monitors CPU temperatures and adjusts CPU frequencies and fan speeds (if connected to the hardware module)
based on predefined temperature curves specified in the configuration file.

For more information about the TempTamer bash script, please see [src/linux/README.md](src/linux/README.md).

## Preparing and Installing the Hardware Module

1. Connect your Arduino or ESP32 board to your computer.
2. Upload the appropriate firmware to your microcontroller.
3. Connect your PWM fans and optionally Dallas temperature probe to the microcontroller.
4. Launch the serial monitor in the Arduino IDE or any serial communication software.
5. Send commands in the format `{command,param1,param2,...}` to control fan speeds and retrieve temperature readings.

### Hardware Example

![](TempTamer_Circuit_Schematic.png)

For more information about TempTamer Hardware Module, please see [src/arduino/README.md](src/arduino/README.md).

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
