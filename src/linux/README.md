# TempTamer Shell Script

## About

TempTamer Shell Script provides dynamic temperature-based control over CPU frequencies and fan speeds on Linux systems.
It regulates CPU performance to maintain optimal temperatures, ensuring system stability and longevity.

## Requirements

- Linux-based system
- CPU temperature monitoring capabilities
- Optional: TempTamer Fan Controller Module for fan speed control

## Configuration

1. Clone the TempTamer repository to your local machine.
2. Create a new configuration file (you can use `tempTamer.config.sample` as a template) with a text editor.
3. Configure the configuration file variables to match your system setup and preferences.
4. Save changes.

## Configuration with Hardware Module

If you have the TempTamer Fan Controller Module installed:
1. Follow the hardware setup instructions provided with the module.
2. Ensure that the serial device path (`fanSerialDevice`) in the configuration file points to the correct device.
3. Specify the number of fans (`noOfFans`) connected to the module.
4. Adjust the fan speed curves in the configuration file to match your cooling requirements.

## Starting + Command Line Options

To start TempTamer:
1. Open a terminal window.
2. Navigate to the directory containing the script (`tempTamer.sh`).
3. Run the script using the following command:

```bash
./tempTamer.sh -t SECONDS_TO_RUN -c CONFIG_FILE
```

Command Line Options:
- `-t SECONDS_TO_RUN`: Specify the duration (in seconds) for which TempTamer will run.
- `-c CONFIG_FILE`: Specify the path to the configuration file.
- `-h`: Displays help.

Example usage:
```bash
./tempTamer.sh -t 62 -c config.txt
```

This command starts TempTamer, running for 62 seconds, using the configuration specified in `config.txt`.

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
