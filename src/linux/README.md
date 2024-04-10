# TempTamer Shell Script

## About

TempTamer Shell Script provides dynamic temperature-based control over CPU frequencies and fan speeds on Linux systems. It regulates CPU performance to maintain optimal temperatures, ensuring system stability and longevity.

## Requirements

- Linux-based system
- CPU temperature monitoring capabilities
- Optional: TempTamer Fan Controller Module for fan speed control

## Configuration

1. Clone the TempTamer repository to your local machine.
2. Open the shell script (`temptamer.sh`) in a text editor.
3. Configure the script variables to match your system setup and preferences.
4. Save the changes to the script.

## Configuration with Hardware Module

If you have the TempTamer Fan Controller Module installed:

1. Follow the hardware setup instructions provided with the module.
2. Ensure that the serial device path (`fanSerialDevice`) in the configuration file points to the correct device.
3. Specify the number of fans (`noOfFans`) connected to the module.
4. Adjust the fan speed curves in the configuration file to match your cooling requirements.

## Starting + Command Line Options

To start TempTamer:

1. Open a terminal window.
2. Navigate to the directory containing the script (`temptamer.sh`).
3. Run the script using the following command:

```bash
./temptamer.sh -t SECONDS_TO_RUN -c CONFIG_FILE
```

Command Line Options:

- `-t SECONDS_TO_RUN`: Specify the duration (in seconds) for which TempTamer will run.
- `-c CONFIG_FILE`: Specify the path to the configuration file.

Example usage:

```bash
./temptamer.sh -t 3600 -c config.txt
```

This command starts TempTamer, running for 3600 seconds (1 hour), using the configuration specified in `config.txt`.

## Safety Considerations

- Ensure that the hardware module (if used) is correctly connected and configured to prevent damage to your system.
- Monitor system behavior closely, especially when adjusting fan speed curves and temperature thresholds.

## Support

For any questions, issues, or feedback, please open an issue on GitHub. We're here to help and continuously improve TempTamer. Happy temp taming!