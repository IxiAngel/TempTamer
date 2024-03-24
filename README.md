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
  
### Serial Communication
- Ability to set configuration options via serial communication.

## Getting Started

### Prerequisites
- ESP32 microcontroller or Arduino*
- PWM-compatible fans
- Dallas DS18B20 temperature probe (Optional)
- Compatible computer with CPU temperature monitoring capabilities

*Arduino and ESP8266(D1) use SoftPWM, while ESP32 uses more accurate LEDC for PWM fan control.

### Installation
1. Clone the TempTamer repository to your local machine.
2. Connect your Arduino or ESP32 board to your computer.
3. Upload the appropriate firmware to your microcontroller.
4. Connect your PWM fans and Dallas temperature probe to the microcontroller.
5. Configure TempTamer settings according to your preferences.
6. Run TempTamer and enjoy The Cool CPU Commander.

## Flashing Procedure for Arduino or ESP32

Follow the steps below to successfully flash the .bin files onto your device.

### Prerequisites

Before you begin, ensure you have the following:

- [Arduino IDE](https://www.arduino.cc/en/software) or [ESP-IDF Toolchain](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#installation-step-by-step) installed on your system.
- USB cable to connect your microcontroller to your computer.
- The .bin file(s) you intend to flash onto your device.

### Procedure

1. **Connect your Microcontroller**: Connect your Arduino or ESP32 microcontroller to your computer using the USB cable.

2. **Open Arduino IDE or ESP-IDF Terminal**: Open the Arduino IDE or the ESP-IDF terminal, depending on your microcontroller.

3. **Select the Correct Port**: In the Arduino IDE, navigate to `Tools > Port` and select the appropriate port for your microcontroller.

4. **Enter Bootloader Mode (for ESP32 Only)**: If you're flashing a .bin file onto an ESP32 microcontroller, you might need to enter bootloader mode. Usually, this involves holding down the BOOT button while resetting the device.

5. **Flash the .bin File**:

   - **Arduino IDE**:
     1. In the Arduino IDE, navigate to `Sketch > Include Library > Add .ZIP Library`.
     2. Select the .zip file containing the .bin file you want to flash.
     3. Once the library is added, navigate to `File > Examples` and select the library you just added.
     4. Open the example sketch and verify/upload it to your microcontroller.

   - **ESP-IDF Terminal**:
     1. Navigate to the directory containing the .bin file using the terminal.
     2. Use the `esptool.py` utility to flash the .bin file onto your ESP32 microcontroller. The command typically looks like this:

      ```
      esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x1000 your_firmware.bin
      ```

      Replace `/dev/ttyUSB0` with the appropriate port for your microcontroller, and `your_firmware.bin` with the name of your .bin file.

6. **Verify**: Once the flashing process is complete, verify that the .bin file has been successfully flashed onto your microcontroller.

7. **Reset (if necessary)**: Reset your microcontroller if required to start running the flashed program.

### Troubleshooting

- If you encounter any errors during the flashing process, double-check your connections and ensure you're using the correct port and commands.
- Ensure that your .bin file is compatible with your microcontroller and that it has been generated correctly.

Following these steps should allow you to successfully flash .bin files onto your Arduino or ESP32 microcontroller. If you encounter any issues, refer to the troubleshooting section or consult the documentation specific to your device or development environment.

## Usage

### Configurations

The `config.h` file contains various configurations for the TempTamer Fan Controller Module. Here's a breakdown of each configuration option:

### Macro Definitions

#### USE_LEDC
Defines whether the LEDC module is used for controlling fan speeds.

#### Fan Ports

```cpp
const int FANS[6] = { GPIO_NUM_19, GPIO_NUM_18, GPIO_NUM_5, GPIO_NUM_17, GPIO_NUM_16, GPIO_NUM_4 };
```
Specifies the GPIO pins used for connecting the fans. Modify this array to match your hardware configuration.

#### Initial Fan Speed

```cpp
const int INITIAL_FAN_SPEED = 50;
```
Sets the initial speed of the fans when the module is powered on or reset. The value ranges from 0 to 100.

#### Minimum Fan Speed

```cpp
int MIN_FAN_SPEED = 10;
```
Prevents setting fan speeds below this threshold to ensure proper airflow. Adjust as needed.

#### Emergency Timeout

```cpp
int EMERGENCY_TIMEOUT = 60;
```
If no data is received for this duration (in seconds), all fans will be set to maximum speed as a safety measure.

#### Temperature Sensor

```cpp
int TEMP_SENSOR_PIN = GPIO_NUM_13;
```
Specifies the GPIO pin used for the temperature sensor. Use -1 to disable temperature monitoring.

### Optional Settings:

- **TEMP_SENSOR_MIN_TEMP**: Set fans to maximum speed if temperature drops to or below this value (in Celsius).
- **TEMP_SENSOR_MAX_TEMP**: Set fans to maximum speed if temperature reaches or exceeds this value (in Celsius).
- **TEMP_SENSOR_MAX_TEMP_FAN_SPEED**: Set fans to a specific speed when the temperature exceeds the maximum threshold.

Example:

```cpp
// Enable temperature sensor and set temperature thresholds
#define TEMP_SENSOR_PIN GPIO_NUM_13
const int TEMP_SENSOR_MIN_TEMP = 20;  // Set fans to max speed if temperature drops below 20°C
const int TEMP_SENSOR_MAX_TEMP = 80;  // Set fans to max speed if temperature exceeds 80°C
const int TEMP_SENSOR_MAX_TEMP_FAN_SPEED = 90;  // Set fans to 90% speed when temperature exceeds 80°C
```

Modify these configurations according to your specific requirements and hardware setup.

This section provides insights into configuring the fan controller module according to your specific needs and hardware setup.

CPU Frequency and Fan curves.
They must start with the highest temperature and end with
the lowest temperature.
Temperature, CPU Frequency, Timeout, FanBits=FanSpeed, ...
```cpp
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
```

### Manual Usage

1. Launch the serial monitor in the Arduino IDE or any serial communication software.
2. Send commands in the format "{command,param1,param2,...}" to control fan speeds and retrieve temperature readings.
3. Refer to the provided commands for setting fan speeds, retrieving temperatures, and configuring options.

### Serial PC App

TempTamer comes with a companion linux app for convenient monitoring and control of CPU temperatures, fan and clock speeds. The app offers the following features:

1. **Real-Time Monitoring:** Monitor CPU temperatures, clock and fan speeds in real-time.
2. **Manual Control:** Adjust fan speeds and CPU clock manually to meet specific cooling requirements.
3. **Automatic Optimization:** Let TempTamer automatically optimize settings based on temperature readings.
4. **Email Notifications:** Receive email notifications when critical temperatures are reached, ensuring timely intervention.
5. **Safety Features:** The app includes safety features to prevent hardware damage due to inadequate cooling or incorrect configurations.

To use the Serial PC app:

1. **Launch TempTamer on your computer:** Ensure TempTamer is running on your system.
2. **Connect via Serial Communication:** Use serial communication software to establish a connection with TempTamer.
3. **Monitor and Control:** Monitor CPU temperatures and fan speeds, and adjust settings as needed.
4. **Stay Informed:** Stay informed about critical temperature events via email notifications.

### Fan Controller Module

The TempTamer Fan Controller Module is a crucial component of the TempTamer system, responsible for managing fan speeds based on user commands received via serial communication. Below is an overview of the functionalities provided by this part of the application:

#### Functionality Overview

1. **`void setFanSpeed(int fanIndex, int percent)`:**
   - Description: Sets the speed of a single fan based on the provided percentage.
   - Parameters:
     - `fanIndex`: Index of the fan whose speed needs to be set.
     - `percent`: Speed percentage (0-100) to set for the fan.

2. **`void setMultiFanSpeed(long fanBits, int percent)`:**
   - Description: Sets the speed of multiple fans based on a bitmask and the provided percentage.
   - Parameters:
     - `fanBits`: Bitmask representing which fans to set the speed for.
     - `percent`: Speed percentage (0-100) to set for the selected fans.

3. **`void initFans(int percent)`:**
   - Description: Initializes the fans, setting them to a specified initial speed percentage.
   - Parameters:
     - `percent`: Initial speed percentage (0-100) for all fans.

4. **`boolean handleFanCommand(String data)`:**
   - Description: Handles a single fan command received via serial communication.
   - Parameters:
     - `data`: String containing the fan command in the format "{fanIndex},{fanSpeed}".
   - Returns: `true` if the command was successfully processed, `false` otherwise.

5. **`boolean handleMultiFanCommand(String data)`:**
   - Description: Handles a multi-fan command received via serial communication.
   - Parameters:
     - `data`: String containing the multi-fan command in the format "{fanBits=FanSpeed,...}".
   - Returns: `true` if the command was successfully processed, `false` otherwise.

## Safety Considerations

- Ensure that the fan controller module is correctly connected and configured to avoid damaging hardware due to inadequate cooling.
- Use caution when defining fan speed curves and temperature thresholds to prevent overheating and oscillations.

## Contributions

Contributions to TempTamer are welcome! Whether you're a seasoned developer or a newcomer, we appreciate all contributions that help improve TempTamer for the community. Please see our [Contribution Guidelines](link-to-guidelines) for more information.

## Support

For any questions, issues, or feedback, please open an issue on GitHub. We're here to help and continuously improve TempTamer for all users.

Feel free to customize this README to include specific instructions, links, or additional details about your application. Happy coding!
