# TempTamer: The Cool CPU Commander

## About

TempTamer is the ultimate solution for controlling CPU clock and fan speeds with finesse, ensuring optimal performance while keeping temperatures and CPU stability in check. It consists of two modules: a bash script for Linux systems and a hardware module for controlling fan speeds and CPU frequencies.

## Requirements

- Compatible computer with CPU temperature monitoring capabilities
- PWM-compatible fans
- Dallas DS18B20 temperature probe (Optional)
- ESP32 microcontroller or Arduino

## Configuring and Starting TempTamer Shell Script on Linux

1. Clone the TempTamer repository to your local machine.
2. Navigate to the directory containing the bash script.
3. Make the script executable using the command: `chmod +x temptamer.sh`
4. Open the script and configure the temperature thresholds and fan speed curves according to your requirements.
5. Run the script using the command: `./temptamer.sh`

The bash script constantly monitors CPU temperatures and adjusts CPU frequencies and fan speeds based on predefined temperature curves specified in the configuration file.

## Preparing and Installing the Hardware Module

1. Connect your Arduino or ESP32 board to your computer.
2. Upload the appropriate firmware to your microcontroller.
3. Connect your PWM fans and Dallas temperature probe to the microcontroller.
4. Configure TempTamer settings according to your preferences in the `config.h` file.
5. Adjust fan ports, initial fan speed, minimum fan speed, and temperature sensor settings as needed.
6. Compile and upload the firmware to your microcontroller.

## Interfacing with TempTamer Hardware Module

1. Launch the serial monitor in the Arduino IDE or any serial communication software.
2. Send commands in the format "{command,param1,param2,...}" to control fan speeds and retrieve temperature readings.
3. Refer to the provided commands for setting fan speeds, retrieving temperatures, and configuring options.

## Safety Considerations

- Ensure that the fan controller module is correctly connected and configured to avoid damaging hardware due to inadequate cooling.
- Use CAUTION when defining fan speed curves and temperature thresholds to prevent overheating and oscillations.
- Follow the safety principles or else there will be problems!

## Contributions

Contributions to TempTamer are welcome! Whether you're a seasoned developer or a newcomer, we appreciate all contributions that help improve TempTamer for the community.

## Support

For any questions, issues, or feedback, please open an issue on GitHub. We're here to help and continuously improve TempTamer for all users.