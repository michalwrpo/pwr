# -----------------
# Script showing information about system until interrupted
# Michał Waluś 2024
# -----------------

# initializes variables that shouldn't change during working of the script or that need to be initialized
init () { 
    core_num=$(cat /proc/stat | grep -E "cpu[0-9]" -c)
    battery_full=$(cat /sys/class/power_supply/BAT0/uevent | grep ENERGY_FULL= | cut -d "=" -f 2)
    memory_total=$(head -n 1 /proc/meminfo | xargs | cut -d " " -f 2  | numfmt --from-unit=ki --to=iec --format=%.2f)

    dtotalprev=$(cat /proc/net/dev | grep "wlan0" | xargs | cut -d " " -f 10) 
    utotalprev=$(cat /proc/net/dev | grep "wlan0" | xargs | cut -d " " -f 2)
    download=(0 0 0 0 0 0 0 0 0 0)
    upload=(0 0 0 0 0 0 0 0 0 0)

    get_cpu # information about cpu and network are measured in relation to last second
    get_net # so we need to run these functions once before the others
}

# updates information about network
get_net () {
    net_dev=$(cat /proc/net/dev | grep "wlan0" | xargs)
    for i in {0..8}; do 
        download[$i]=${download[$(($i + 1))]}
        upload[$i]=${upload[$(($i + 1))]}
    done

    # saves numbers stored in /proc/net/dev so that download and upload have change compared to last second
    dtotal=$(cut -d " " -f 10 <<< $net_dev)
    utotal=$(cut -d " " -f 2 <<< $net_dev)

    download[9]=$(($dtotal - $dtotalprev))
    upload[9]=$(($utotal - $utotalprev))
    
    dtotalprev=$dtotal
    utotalprev=$utotal

    # finds maximums to allow us to better scale graphs later
    dmax=${download[0]}
    umax=${upload[0]}
    for i in {1..8}; do
        (( ${download[$i]} > $dmax )) && dmax=${download[$i]}
        (( ${upload[$i]} > $umax )) && umax=${upload[$i]}
    done
}

# gets information about every cpu core idle time
get_cpu() {
    cpu_idle=()
    cpu_total=$(bc <<< "$(cut -d " " -f 1 /proc/uptime) * 100" | cut -d "." -f 1)
    cpu_stat=$(cat /proc/stat | grep -E "cpu[0-9]" | xargs)
    for i in $(seq 0 $(($core_num - 1))); do 
        cpu_idle+=($(echo $cpu_stat | cut -d " " -f $((11 * $i + 5))))
    done
}

# calculates cpu usage in %
calculate_cpu() {
    cpu_idle_prev=(${cpu_idle[@]})
    cpu_total_prev=$cpu_total

    get_cpu
    totaldiff=$(($cpu_total - $cpu_total_prev))

    cpu_usage=()
    for i in $(seq 0 $(($core_num - 1))); do
        idlediff=$((${cpu_idle[$i]} - ${cpu_idle_prev[$i]}))
        cpu_usage+=($(bc <<< "scale=1; 100 - 100 * $idlediff / $totaldiff"))
    done

}

# gets system uptime in days, hours, minutes and seconds
get_uptime () {
    uptime_seconds=$(cut -d " " -f 1 /proc/uptime | cut -d "." -f 1)
    uptime_days=$(bc <<< "$uptime_seconds / 86400")
    uptime_seconds=$(bc <<< "$uptime_seconds - $uptime_days * 86400")
    uptime_hours=$(bc <<< "$uptime_seconds / 3600")
    uptime_seconds=$(bc <<< "$uptime_seconds - $uptime_hours * 3600")
    uptime_minutes=$(bc <<< "$uptime_seconds / 60")
    uptime_seconds=$(bc <<< "$uptime_seconds - $uptime_minutes * 60")
}

# gets current battery level in percentage
get_battery () {
    battery_now=$(cat /sys/class/power_supply/BAT0/uevent | grep ENERGY_NOW= | cut -d "=" -f 2)
    battery_percentage=$(bc <<< "scale=2; 100*$battery_now/$battery_full")
}

# get system load
get_load () {
    load=$(cut -d " " -f 1-3 /proc/loadavg)
}

# gets information about free and availabe memory 
get_memory () {
    mem_info=$(head -n 3 /proc/meminfo | tail -n 2)
    mem_free=$(head -n 1 <<< $mem_info | xargs | cut -d " " -f 2 | numfmt --from-unit=ki --to=iec --format=%.2f)
    mem_available=$(tail -n 1 <<< $mem_info | xargs | cut -d " " -f 2 | numfmt --from-unit=ki --to=iec --format=%.2f)
}

# graphs internet download and upload from last 10 seconds
graph () {
    if [[ $dmax > 0 ]]; then
        for i in {0..9}; do
            dratio[$i]=$(( (10 * ${download[$i]} + ( $dmax >> 2 ) ) / $dmax * 10 ))
        done
    else
        dratio=(0 0 0 0 0 0 0 0 0 0)
    fi

    if [[ $umax > 0 ]]; then
        for i in {0..9}; do
            uratio[$i]=$(( (10 * ${upload[$i]} + ( $umax >> 2 ) ) / $umax * 10 ))
        done
    else
        uratio=(0 0 0 0 0 0 0 0 0 0)
    fi

    echo "Download graph" && tput cup 19 25 && echo "Upload graph"
    for i in {0..9}; do
        for j in {1..10}; do
            if [ ${dratio[$i]} -ge $(($j * 10)) ]; then
                tput cup $((30 - $j)) $((2 * $i)) && echo -e "\x1b[97;107m--\x1b[39;49m"
            fi
            if [ ${uratio[$i]} -ge $(($j * 10)) ]; then
                tput cup $((30 - $j)) $((25 + 2*$i)) && echo -e "\x1b[97;107m--\x1b[39;49m"
            fi
        done
    done
    tput cup 30 0
}

# shows information about system
update () {
    get_net
    calculate_cpu
    get_uptime
    get_battery
    get_load
    get_memory

    echo "System status"
    echo -n "Download: " && echo "$(numfmt --to=iec <<< ${download[9]})B/s"
    echo -n "Upload: " && echo "$(numfmt --to=iec <<< ${upload[9]})B/s"
    for i in $(seq 0 $(($core_num - 1))); do
        # 2nd parameter is cpu frequency which is easily accesible and isn't needlessly stored in variable
        echo "cpu$i: ${cpu_usage[$i]}% | $(cat /sys/devices/system/cpu/cpu$i/cpufreq/scaling_cur_freq)"
    done
    echo "Uptime: ${uptime_days}d ${uptime_hours}h ${uptime_minutes}m ${uptime_seconds}s"
    echo "Battery: ${battery_percentage}%"
    echo "Average load (over last 1/5/15minutes): $load"
    echo "Available memory: ${mem_available}B/${memory_total}B (${mem_free}B free)"

    graph
}

# initlizes program
init

# while true loop making program run every second until it's interrupted 
while :
do
    sleep 1
    clear
    update
done
