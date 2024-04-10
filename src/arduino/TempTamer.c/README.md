# TempTamer Hardware Module

## About

The TempTamer Hardware Module complements the TempTamer Shell Script, providing fan speed control capabilities based on real-time temperature readings. With this module, you can efficiently manage CPU temperatures and fan speeds for optimal system performance and reliability.

## Quick Prep/Start from Pre-built Binaries

1. Download the pre-built binaries for your platform from the TempTamer GitHub releases page.
2. Connect the TempTamer Hardware Module to your computer via the appropriate interface (e.g., USB).
3. Ensure that the necessary drivers are installed if required by your operating system.
4. Run the executable file to start using TempTamer immediately.

## Protocol/Interface

The TempTamer Hardware Module communicates with the system using a serial interface. It accepts commands in a specific format to adjust fan speeds based on temperature readings received from the system.

### Command Format:

```
{fan_speed_command}
```

- `fan_speed_command`: A command to set the fan speed, formatted as `{fan_bits=fan_speed}`.

Example:
```
{110=75}
```
This command sets the fan speed of the fans associated with the bit pattern `110` to 75%.

## Build from Source

If you prefer to build TempTamer Hardware Module from source:

1. Clone the TempTamer repository to your local machine.
2. Navigate to the `arduino` directory.
3. Follow the build instructions provided in the README or build script.
4. Once built, connect the hardware module to your computer and proceed with configuration and usage.

...

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
- **Configuration**: Download and manufacture the PCB via JLC-PCB or simmialr, program the microcontroller.
- **Usage**: Connect fans, power and temperature probe to the custom PCB HAT with Arduino or ESP32. 

---

This README provides an overview of the TempTamer Hardware Module, including quick start instructions, protocol/interface details, building from source, and examples of different hardware configurations. Choose the setup that best fits your requirements and hardware expertise.
