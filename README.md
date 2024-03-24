# TempTamer: The Cool CPU Commander

Welcome to TempTamer, your ultimate solution for controlling CPU clock and fan speeds with finesse. Say goodbye to stability issues and system freezes – TempTamer is here to keep your system running smoothly and quietly.

## Features

### Dynamic CPU Clock Control
TempTamer intelligently adjusts CPU clock speeds based on real-time temperature readings, ensuring optimal performance while keeping temperatures and CPU stability in check.

### PWM Fan Control
Take full control of your computer's fans and CPU frequency, effortlessly managing fan speeds for optimal cooling efficiency and stability.

- Dynamic fan speed control based on temperature readings.
- Support for single and multiple fan configurations.
- *External temp. probe. (*Optional. Uses external library OneWire.h and DallasTemperature.h)
  

### Serial Comunication
- Ability to set configuration options via serial communication.


## Getting Started

### Prerequisites
- ESP32 microcontroller or Arduino*
- PWM-compatible fans
- Dallas DS18B20 temperature probe (Optional)
- Compatible computer with CPU temperature monitoring capabilities

  *Arduino and ESP8266(D1) use SoftPWM, while ESP32 uses more accurate LEDC for PWM fan controll.

### Installation
1. Clone the TempTamer repository to your local machine.
2. Connect your Arduino or ESP32 board to your computer.
3. Upload the appropriate firmware to your microcontroller.
4. Connect your PWM fans and Dallas temperature probe to the microcontroller.
5. Configure TempTamer settings according to your preferences.
6. Run TempTamer and enjoy The Cool CPU Commander.

## Usage

### Configuration File Template

# TempTamer Configuration File

# Script identifier, useful for tagging script instances when sending a critical temperature email.
identifier=Your Computer

# Send email when specified critical temperature is reached.
criticalTemperature=95

# E-Mail address to send to when critical temperature is reached.
email=

# Fan Controller Module Serial Device path, if it is used.
fanSerialDevice=/dev/ttyUSB0

# How many fans are attached to the Fan Controller Module.
noOfFans=6

# Command to read the CPU1 temperature with.
getCpu1TempCmd=</sys/class/thermal/thermal_zone1/temp

# Command to read the CPU2 temperature with.
getCpu2TempCmd=</sys/class/thermal/thermal_zone2/temp

# Divide obtained temperature from above commands with this divisor.
cpuTempDivisor=1000

# Minimum cool down in seconds.
minCoolDown=3

# CPU Frequency and Fan curves.
# They must start with the highest temperature and end with
# the lowest temperature.
# Temperature, CPU Frequency, Timeout, FanBits=FanSpeed, ...
curve=101,1800000,0,0=100
curve=100,2100000,2,0=100
curve=99,2700000,4,0=100
curve=98,3000000,6,0=100
curve=97,3200000,8,0=100
curve=96,3300000,10,0=100
curve=90,3700000,12,9=90,36=100
curve=85,3700000,15,9=80,36=100
curve=80,3700000,20,9=50,36=90
curve=75,3700000,25,9=45,36=60
curve=65,3700000,30,9=30,36=40
curve=0,3700000,33,0=20


###Manual
1. Launch the serial monitor in the Arduino IDE or any serial communication software.
2. Send commands in the format "{command,param1,param2,...}" to control fan speeds and retrieve temperature readings.
3. Refer to the provided commands for setting fan speeds, retrieving temperatures, and configuring options.

###Serial PC app

1. Launch TempTamer on your computer.
2. Monitor CPU temperatures and fan speeds in real-time.
3. Adjust fan speeds manually or let TempTamer automatically optimize settings.
4. Stay cool and productive while TempTamer takes care of the rest!




## Safety Considerations
- Ensure that the fan controller module is correctly connected and configured to avoid damaging hardware due to inadequate cooling.
- Use caution when defining fan speed curves and temperature thresholds to prevent overheating and oscilations.

## Contributions

Contributions to TempTamer are welcome! Whether you're a seasoned developer or a newcomer, we appreciate all contributions that help improve TempTamer for the community. Please see our [Contribution Guidelines](link-to-guidelines) for more information.

## Support

For any questions, issues, or feedback, please open an issue on GitHub. We're here to help and continuously improve TempTamer for all users.

Feel free to customize this README to include specific instructions, links, or additional details about your application. Happy coding!
