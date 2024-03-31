### Linux Bash Script

TempTamer comes with a companion linux script for convenient monitoring and control of CPU temperatures, fan and clock speeds.
#### Features:
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
   - Sets the speed of a single fan based on the provided percentage.
     - `fanIndex`: Index of the fan whose speed needs to be set.
     - `percent`: Speed percentage (0-100) to set for the fan.

2. **`void setMultiFanSpeed(long fanBits, int percent)`:**
   - Sets the speed of multiple fans based on a bitmask and the provided percentage.
     - `fanBits`: Bitmask representing which fans to set the speed for.
     - `percent`: Speed percentage (0-100) to set for the selected fans.

3. **`void initFans(int percent)`:**
   - Initializes the fans, setting them to a specified initial speed percentage.
     - `percent`: Initial speed percentage (0-100) for all fans.

4. **`boolean handleFanCommand(String data)`:**
   - Handles a single fan command received via serial communication.
     - `data`: String containing the fan command in the format "{fanIndex},{fanSpeed}".
   - `true` if the command was successfully processed, `false` otherwise.

5. **`boolean handleMultiFanCommand(String data)`:**
   - Handles a multi-fan command received via serial communication.
     - `data`: String containing the multi-fan command in the format "{fanBits=FanSpeed,...}".
   - `true` if the command was successfully processed, `false` otherwise.
