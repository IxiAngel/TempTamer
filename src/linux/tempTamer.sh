#!/bin/bash -e

# MIT License
#
# Copyright (c) 2024 TempTamer Developers
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

VERSION="1.0"

# Set with argument -t
MAX_RUNNING_TIME=0

# Set with argument -c
CONFIG_FILE=""

# Below variables are set with configuration file
FAN_SERIAL_DEV=""
NO_OF_NODES=1
NO_OF_FANS=0
CURVES=()

GET_CPU1_TEMP_CMD=""
GET_CPU2_TEMP_CMD=""

CRITICAL_TEMPERATURE=95
EMAIL=""
IDENTIFIER="Your Computer"

CPU_TEMP_DIVISOR=1000

MIN_COOL_DOWN=3
# End of configuration file variables

LAST_FREQ=`</sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq`
LAST_FREQ_UPDATE=0

START_TIME=$SECONDS

# ("curve temperature,fan speed,updated time")
FAN_STATE=()

# Used to return state from updateFanState
RETURNED_FAN_STATE=()

FANS_UPDATED=0

showCurrentCoreFrequencies()
{
  echo "Current core frequencies:"
  cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq | sort | uniq -c
  echo
}

setScalingMaxFreq()
{
  echo Setting frequencies of Node$1 to $2

  for dir in /sys/devices/system/node/node$1/cpu*/cpufreq;
  do
    echo "$2" > $dir/scaling_max_freq
  done
}

setFrequency()
{
  if [ $LAST_FREQ -ne $1 ]; then
    if [ $LAST_FREQ -gt $1 ] || [ $(($SECONDS - $LAST_FREQ_UPDATE)) -ge $2 ]; then
      LAST_FREQ=$1
      LAST_FREQ_UPDATE=$(($MIN_COOL_DOWN + $SECONDS - $2))
      local i=0
      while [ $i -lt $NO_OF_NODES ]; do
        setScalingMaxFreq $i $1
        i=$(($i + 1))
      done
    fi
  fi
}

setFanSpeed()
{
  if [ "$FAN_SERIAL_DEV" == "" ] || [ ! -c $FAN_SERIAL_DEV ]; then
    echo "Cannot set fan speed, specified serial device does not exist."
    return
  fi

  #echo "Setting Fan Speed with command: {1$1}"
  printf "{1$1}" > $FAN_SERIAL_DEV
}

setAllFans()
{
  if [ "$FAN_SERIAL_DEV" == "" ] || [ ! -c $FAN_SERIAL_DEV ]; then
    return
  fi

  local cpuTemp=$1
  shift
  local curveTemp=$1
  shift
  local curveSpeeds=$1
  shift
  local curveTimeout=$1
  shift
  local curveFound=$1
  shift
  local prevCurveFanStates=("$@")

  local temperatureLowerThanCurve=0
  if [ $cpuTemp -lt $curveTemp ]; then
    temperatureLowerThanCurve=1
  fi

  local speed=""

  local updateTime=$SECONDS
  local fanCommand=""

  while [ "$speed" != "$curveSpeeds" ]; do
    local speed=${curveSpeeds%%,*}

    curveSpeeds=${curveSpeeds#*,}

    local fanBits=${speed%%=*}
    local fanSpeed=${speed#*=}

    local i=0
    while [ $i -lt $NO_OF_FANS ]; do
      local bitMask=$((1 << $i))
      if [ $fanBits -eq 0 ] || [ $(($fanBits & $bitMask)) -eq $bitMask ]; then
        local prevCurveTemp=${prevCurveFanStates[$i]%%,*}
        if [ "$prevCurveTemp" == "" ]; then
          prevCurveTemp=200
        fi

        local prevCurveFanSpeed=${prevCurveFanStates[$i]#*,}
        prevCurveFanSpeed=${prevCurveFanSpeed%%,*}
        if [ "$prevCurveFanSpeed" == "" ]; then
          prevCurveFanSpeed=100
        fi

        local lastFanUpdateTemp=${FAN_STATE[$i]%%,*}
        if [ "$lastFanUpdateTemp" == "" ]; then
          lastFanUpdateTemp=0
        fi

        local lastFanSpeed=${FAN_STATE[$i]#*,}
        lastFanSpeed=${lastFanSpeed%%,*}
        if [ "$lastFanSpeed" == "" ]; then
          lastFanSpeed=0
        fi

        local lastFanUpdate=${FAN_STATE[$i]#*,*,}
        if [ "$lastFanUpdate" == "" ]; then
          lastFanUpdate=0
        fi

        local adjFanSpeed=$(($fanSpeed + (($cpuTemp - $curveTemp) * ($prevCurveFanSpeed - $fanSpeed) / ($prevCurveTemp - $curveTemp))))
        if [ $temperatureLowerThanCurve -eq 1 ]; then
          adjFanSpeed=$fanSpeed
        fi

        if [ $adjFanSpeed -gt 100 ]; then
          adjFanSpeed=100
        fi

        if [ "$adjFanSpeed" != "$lastFanSpeed" ]; then
          if [ $temperatureLowerThanCurve -eq 1 ]; then
            if [ $lastFanSpeed -le $adjFanSpeed ]; then
              break
            fi
          fi
          #echo "$i: $fanSpeed + (($cpuTemp - $curveTemp) * ($prevCurveFanSpeed - $fanSpeed) / ($prevCurveTemp - $curveTemp))=$adjFanSpeed"
          #echo "$i: [ $lastFanSpeed -lt $adjFanSpeed ] || [ $(($updateTime - $lastFanUpdate)) -ge $curveTimeout ]"
          if [ $lastFanSpeed -lt $adjFanSpeed ] || [ $(($updateTime - $lastFanUpdate)) -ge $curveTimeout ]; then
            if [ $curveFound -eq 0 ] || [ $curveFound -ne $lastFanUpdateTemp ]; then
              #echo "$i: $curveTemp,$adjFanSpeed,$(($MIN_COOL_DOWN + $updateTime - $curveTimeout))"
              FAN_STATE[$i]="$curveTemp,$adjFanSpeed,$(($MIN_COOL_DOWN + $updateTime - $curveTimeout))"
              fanCommand="$fanCommand,$bitMask=$adjFanSpeed"
            fi
          fi
        fi
      fi
      i=$(($i + 1))
    done
  done
  if [ "$fanCommand" != "" ]; then
    setFanSpeed $fanCommand
    FANS_UPDATED=1
    return
  fi
}

updateFanState()
{
  local curveTemp=$1
  shift
  local curveSpeeds=$1
  shift
  local dontReplaceStates=$1
  shift

  RETURNED_FAN_STATE=("$@")

  local speed=""

  while [ "$speed" != "$curveSpeeds" ]; do
    local updateTime=0
    local speed=${curveSpeeds%%,*}

    curveSpeeds=${curveSpeeds#*,}

    local fanBits=${speed%%=*}
    local fanSpeed=${speed#*=}

    local i=0
    while [ $i -lt $NO_OF_FANS ]; do
      local bitMask=$((1 << $i))
      if [ $fanBits -eq 0 ] || [ $(($fanBits & $bitMask)) -eq $bitMask ]; then
        if [ $dontReplaceStates -eq 0 ] || [ "$RETURNED_FAN_STATE[$i]" == "" ]; then
          RETURNED_FAN_STATE[$i]="$curveTemp,$fanSpeed,$updateTime"
        fi
      fi
      i=$(($i + 1))
    done
  done
}

readConfigFile()
{
  if [ ! -f "$1" ]; then
    help "Configuration file '$1' does not exist."
  fi

  CURVES=()
  local curveIndex=0
  local line=""
  while read -r line;
  do
    local key=${line[$i]%%=*}
    local value=${line[$i]#*=}
    if [ "$line" == "" ]; then
      continue
    elif [[ $line == \#* ]]; then
      continue
    elif [[ $line == \;* ]]; then
      continue
    elif [ "$key" == "curve" ]; then
      CURVES[$curveIndex]=$value
      curveIndex=$(($curveIndex + 1))
    elif [ "$key" == "fanSerialDevice" ]; then
      FAN_SERIAL_DEV=$value
      if [ ! -c "$value" ]; then
        help "Fan Serial Device '$value' does not exist."
      fi
    elif [ "$key" == "noOfFans" ]; then
      NO_OF_FANS=$value
      if [ "$NO_OF_FANS" == "" ]; then
        help "noOfFans value '$value' is invalid."
      fi
    elif [ "$key" == "noOfNodes" ]; then
      NO_OF_NODES=$value
      if [ "$NO_OF_NODES" == "" ]; then
        help "noOfNodes value '$value' is invalid."
      fi
    elif [ "$key" == "getCpu1TempCmd" ]; then
      GET_CPU1_TEMP_CMD=$value
    elif [ "$key" == "getCpu2TempCmd" ]; then
      GET_CPU2_TEMP_CMD=$value
    elif [ "$key" == "cpuTempDivisor" ]; then
      CPU_TEMP_DIVISOR=$value
    elif [ "$key" == "minCoolDown" ]; then
      MIN_COOL_DOWN=$value
    elif [ "$key" == "criticalTemperature" ]; then
      CRITICAL_TEMPERATURE=$value
    elif [ "$key" == "email" ]; then
      EMAIL=$value
    elif [ "$key" == "identifier" ]; then
      IDENTIFIER=$value
    else
      help "Error reading configuration file '$1' - unknown key '$key'."
    fi
  done < "$1"

  if [ $curveIndex -eq 0 ]; then
    help "Configuration file does not contain any curve data."
  fi

  if [ "$GET_CPU1_TEMP_CMD" == "" ]; then
    help "Configuration file does not contain getCpu1TempCmd option."
  fi

  if [ "$GET_CPU2_TEMP_CMD" == "" ]; then
    help "Configuration file does not contain getCpu2TempCmd option."
  fi

  if [ "$FAN_SERIAL_DEV" != "" ] && [ $NO_OF_FANS -le 0 ]; then
    help "Configuration file has an invalid 'noOfFans=$NO_OF_FANS' value."
  fi
}

initArgs()
{
  while [ $OPTIND -le $# ]
  do
    if getopts ':t:c:h' flag; then
      case $flag in
        t)
          MAX_RUNNING_TIME=$OPTARG
          ;;
        c)
          CONFIG_FILE=$OPTARG
          ;;
        h)
          help
          ;;
        :)
          help "Option '-${OPTARG}' requires an argument."
          ;;
        ?)
          help "Invalid option: '-${OPTARG}'."
          ;;
      esac
    else
      help "Invalid option: '-${OPTARG}'."
    fi
  done

  if [ "$CONFIG_FILE" == "" ]; then
    help "No config file specified."
  fi

  readConfigFile $CONFIG_FILE
}

intro()
{
  echo -e "\x1B[1mTempTamer v$VERSION - The Cool CPU Commander\x1B[0m"
  echo
}

helpText()
{
  intro
  echo -e "\x1B[1mUsage:\x1B[0m ./${0##*/} -t SECONDS_TO_RUN -c CONFIG_FILE"
  echo
  echo "This tool monitors temperatures and regulates CPU Core Frequencies and"
  echo "fan speeds depending on the temperature as defined in the config file."
  echo
  echo "Regulating fan speed is only possible if TempTamer Fan Controller Module"
  echo "is correctly connected and configured."
  echo -e "\x1B[41m\x1B[1m"
  echo "Please be careful if you are using the Fan Controller Module because you can"
  echo "damage your hardware if the module is wired or configured incorrectly or if"
  echo "fan speeds are set too low."
  echo -e "!!! You are using this software at your own risk. !!!\x1B[0m"
  echo
  echo
  echo -e "\x1B[1mExample configuration file:\x1B[0m"
  echo "  # TempTamer Configuration File"
  echo
  echo "  # Script identifier, useful for tagging script instances when"
  echo "  # sending a critical temperature email."
  echo "  identifier=Your Computer"
  echo
  echo "  # Send email when specified critical temperature is reached."
  echo "  criticalTemperature=95"
  echo
  echo "  # E-Mail address to send to when critical temperature is reached."
  echo "  email="
  echo
  echo "  # Fan Controller Module Serial Device path, if it is used."
  echo "  fanSerialDevice=/dev/ttyUSB0"
  echo
  echo "  # How many fans are attached to the Fan Controller Module."
  echo "  noOfFans=6"
  echo
  echo "  # How many processors/nodes does the system have"
  echo "  noOfNodes=1"
  echo
  echo "  # Command to read the CPU1 temperature with."
  echo "  getCpu1TempCmd=</sys/class/thermal/thermal_zone1/temp"
  echo
  echo "  # Command to read the CPU2 temperature with."
  echo "  getCpu2TempCmd=</sys/class/thermal/thermal_zone2/temp"
  echo
  echo "  # Divide obtained temperature from above commands with this divisor."
  echo "  cpuTempDivisor=1000"
  echo
  echo "  # Minimum cool down in seconds."
  echo "  minCoolDown=3"
  echo
  echo "  # CPU Frequency and Fan curves."
  echo "  # They must start with the highest temperature and end with"
  echo "  # the lowest temperature."
  echo "  # Temperature, CPU Frequency, Timeout, FanBits=FanSpeed, ..."
  echo "  curve=101,1800000,0,0=100"
  echo "  curve=100,2100000,2,0=100"
  echo "  curve=99,2700000,4,0=100"
  echo "  curve=98,3000000,6,0=100"
  echo "  curve=97,3200000,8,0=100"
  echo "  curve=96,3300000,10,0=100"
  echo "  curve=90,3700000,12,9=90,36=100"
  echo "  curve=85,3700000,15,9=80,36=100"
  echo "  curve=80,3700000,20,9=50,36=90"
  echo "  curve=75,3700000,25,9=45,36=60"
  echo "  curve=65,3700000,30,9=30,36=40"
  echo "  curve=0,3700000,33,0=20"
  echo
  echo -e "\x1B[41m\x1B[1m$1\x1B[0m"
}

help()
{
  if [ "$1" == "" ]; then
    helpText | more
  else
    helpText "Error: $1"
  fi
  exit 1
}

init()
{
  cd "$(dirname "$0")"

  initArgs "$@"

  intro
  echo "Configuration File: $CONFIG_FILE"
  echo "Identifier: $IDENTIFIER"
  echo "Critical Temperature: $CRITICAL_TEMPERATURE"
  echo "E-Mail Address: $EMAIL"
  echo "Fan Controller Module Serial Device: $FAN_SERIAL_DEV"
  echo "Number of Fans: $NO_OF_FANS"
  echo "Number of Nodes: $NO_OF_NODES"
  echo "Get CPU1 Temperature Command: $GET_CPU1_TEMP_CMD"
  echo "Get CPU2 Temperature Command: $GET_CPU2_TEMP_CMD"
  echo "CPU Temp Divisor: $CPU_TEMP_DIVISOR"
  echo "Min Cool Down: $MIN_COOL_DOWN"
  echo "Curves (Temperature,CPU Frequency,Cool Down,Fan Bits=FanSpeed,...):"

  local curve
  for curve in ${CURVES[@]}; do
    echo $curve
  done
  echo

  local temp1=$(($(eval "$GET_CPU1_TEMP_CMD") / $CPU_TEMP_DIVISOR))
  local temp2=$(($(eval "$GET_CPU2_TEMP_CMD") / $CPU_TEMP_DIVISOR))
  echo "Current Temperatures - Temp1: $temp1°C, Temp2: $temp2°C"
  showCurrentCoreFrequencies


  # Set Baudrate to 115200
  if [ "$FAN_SERIAL_DEV" != "" ]; then
    if [ -c $FAN_SERIAL_DEV ]; then
      stty -F $FAN_SERIAL_DEV 115200
    fi
  fi
}

outputArray()
{
  local arr=($@)
  local i=0
  for i in "${!arr[@]}"; do 
    printf "%s=(%s); " "$i" "${arr[$i]}"
  done
}

startMonitor()
{
  init "$@"

  while [ 1 -eq 1 ]; do
    local temp1=$(($(eval "$GET_CPU1_TEMP_CMD") / $CPU_TEMP_DIVISOR))
    local temp2=$(($(eval "$GET_CPU2_TEMP_CMD") / $CPU_TEMP_DIVISOR))
  
    local cpuTemp=$temp1
    if [ $temp2 -gt $cpuTemp ]; then
      cpuTemp=$temp2
    fi

    local curFreq=$LAST_FREQ

    local prevCurveFanStates=()
    local updatedFans=0
    local curveFound=0
    FANS_UPDATED=0

    local curve
    for curve in ${CURVES[@]}; do
      local curveTemp=${curve%%,*}
    
      local curveFreq=${curve#*,}
      curveFreq=${curveFreq%%,*}
    
      local curveTimeout=${curve#*,*,}
      curveTimeout=${curveTimeout%%,*}
    
      local curveSpeeds=${curve#*,*,*,}

      setAllFans $cpuTemp $curveTemp $curveSpeeds $curveTimeout $curveFound "${prevCurveFanStates[@]}"
      updateFanState $curveTemp $curveSpeeds $curveFound "${prevCurveFanStates[@]}"
      prevCurveFanStates=("${RETURNED_FAN_STATE[@]}")

      if [ $cpuTemp -lt $curveTemp ]; then
        if [ $LAST_FREQ -lt $curveFreq ]; then
          setFrequency $curveFreq $curveTimeout
        fi
      else
        if [ $curveFound -eq 0 ]; then
          setFrequency $curveFreq $curveTimeout
          curveFound=$curveTemp
        fi
      fi
    done

    local changed=0
    if [ $curFreq -ne $LAST_FREQ ]; then
      changed=1
      echo "CPU Frequency changed at Temp1: $temp1°C, Temp2: $temp2°C"
      showCurrentCoreFrequencies
      echo
    fi

    if [ $FANS_UPDATED -eq 1 ]; then
      changed=1
      printf "Fan Speeds changed at Temp1: $temp1°C, Temp2: $temp2°C, Fan States: "
      outputArray "${FAN_STATE[@]}"
      echo
    fi

    if [ "$EMAIL" != "" ] && [ $cpuTemp -ge $CRITICAL_TEMPERATURE ]; then
      echo "Critical temperature reached $cpuTemp°C on '$IDENTIFIER'." | mail -s "[$IDENTIFIER] Critical Temperature" $EMAIL &
    fi

    if [ $MAX_RUNNING_TIME -ne 0 ] && [ $(($START_TIME + $MAX_RUNNING_TIME)) -lt $SECONDS ]; then
      break
    fi

    if [ $changed -eq 0 ]; then
      sleep 0.3
    fi
  done
}

startMonitor "$@"