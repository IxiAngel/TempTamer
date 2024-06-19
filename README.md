# TempTamer: The Cool CPU Commander

## About

TempTamer is the ultimate solution for limiting CPU clock and fan speeds with finesse, ensuring optimal performance while keeping temperatures and CPU stability in check.
TempTamer consists of two modules:
- TempTamer bash script for Linux systems which reads CPU temperature, limits CPU frequencies as configured by the user and interfaces with TempTamer Hardware Module, to control fan speed.
- TempTamer Hardware Module for controlling fan speeds.

## Requirements

- Compatible computer with CPU temperature monitoring capabilities
- PWM-compatible fans
- Dallas DS18B20 temperature probe (Optional)
- ESP32 microcontroller or Arduino

## Configuring and Starting TempTamer Shell Script on Linux

1. Clone the TempTamer repository to your computer.
2. Navigate to the directory containing the bash script.
3. Make the script executable using the command: `chmod +x tempTamer.sh`.
4. Create configuration file and configure the temperature thresholds and fan speed curves according to your requirements.
5. Run the script using the command: `./tempTamer.sh`.

The bash script constantly monitors CPU temperatures and adjusts CPU frequencies and fan speeds (if connected to the hardware module) based on predefined temperature curves specified in the configuration file.

For more information about TempTamer bash script, please see [src/linux/README.md](src/linux/README.md).

## Preparing and Installing the Hardware Module

1. Connect your Arduino or ESP32 board to your computer.
2. Upload the appropriate firmware to your microcontroller.
3. Connect your PWM fans and optionally Dallas temperature probe to the microcontroller.
4. Launch the serial monitor in the Arduino IDE or any serial communication software.
5. Send commands in the format "{command,param1,param2,...}" to control fan speeds and retrieve temperature readings.

For more information about TempTamer Hardware Module, please see [src/arduino/README.md](src/arduino/README.md).

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
