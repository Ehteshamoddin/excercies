Write a shell script that shall log available cpu, memory, disk-space on the system at every 15 minutes interval on a log file stored at /var/log/es-monitor.log (example name of a log). Log line format should be - 
1. YYYY-MM-DD HH:MM:SS (in UTC Timezone) 
2. available-cpu={percentage-cpu-available(combined cpu from 0-100)},
3. available-ram={percentage-ram-available},
4. available-disk-space={percentage-disk-available(this should be printed for all the disk devices attached to the system} 



#!/bin/bash

log_file="/var/log/es-monitor.log"

while true
do
    current_time=$(date -u +"%Y-%m-%d %H:%M:%S")

    # CPU Usage
    cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $8}' | cut -d'%' -f1)

    # Memory Usage
    ram_usage=$(free | grep Mem | awk '{print $4/$2 * 100.0}')

    # Disk Space Usage
    disk_usage=$(df -H | awk '{if(NR>1) print $6,$5}' | tr '\n' ',' | sed 's/,$//')

    # Logging to the file
    # echo "${current_time} available-cpu=${cpu_usage},available-ram=${ram_usage},available-disk-space=${disk_usage}" >> $log_file
    # echo -e "${current_time} available-cpu=${cpu_usage},available-ram=${ram_usage},available-disk-space=${disk_usage}\n" >> $log_file
      echo -e "${current_time}\navailable-cpu=${cpu_usage}\navailable-ram=${ram_usage}\navailable-disk-space=${disk_usage}\n" >> $log_file
    # Wait for 15 minutes
    sleep 900
done



I can try to write a shell script for you. Here is one possible solution:

```bash
#!/bin/bash
# A shell script to log available cpu, memory, disk-space on the system at every 15 minutes interval
# The log file is stored at /var/log/es-monitor.log
# The log line format is:
# YYYY-MM-DD HH:MM:SS (in UTC Timezone), available-cpu={percentage-cpu-available}, available-ram={percentage-ram-available}, available-disk-space={percentage-disk-available for each disk device}

# Get the current date and time in UTC format
DATE=$(date -u +"%Y-%m-%d %H:%M:%S")

# Get the percentage of cpu available by subtracting the cpu usage from 100
CPU_USAGE=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1"%"}')

# Get the percentage of ram available by using the free command
RAM_USAGE=$(free | grep Mem | awk '{print $3/$2 * 100.0"%"}')

# Get the percentage of disk space available for each disk device by using the df command
DISK_USAGE=$(df -h | grep "^/dev" | awk '{print $1"="$5}')

# Append the log line to the log file
echo "$DATE, available-cpu=$CPU_USAGE, available-ram=$RAM_USAGE, available-disk-space=$DISK_USAGE" >> /var/log/es-monitor.log

# Schedule the script to run every 15 minutes using cron
# crontab -e
# Add the following line to the crontab file
# */15 * * * * /path/to/script.sh
```

I hope this helps. 😊

Source: Conversation with Bing, 14/1/2024
(1) github.com. https://github.com/ritterbush/files/tree/fb6d64269e78c864b803bfaa3772bfbf52dd5c63/.local%2Fbin%2Fdwm-scripts%2Fupdate-setxroot.sh.