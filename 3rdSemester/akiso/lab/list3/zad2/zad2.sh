init () {
    core_num=$(cat /proc/stat | grep -E "cpu[0-9]" -c)
    battery_full=$(cat /sys/class/power_supply/BAT0/uevent | grep ENERGY_FULL= | cut -d "=" -f 2)
    memory_total=$(head -n 1 /proc/meminfo | xargs | cut -d " " -f 2  | numfmt --from-unit=ki --to=iec --format=%.2f)

    get_cpu
    get_net
    downzero=$download
    upzero=$upload
}

get_net () {
    net_dev=$(cat /proc/net/dev | grep "wlan0" | xargs)
    download=$(cut -d " " -f 2 <<< $net_dev) 
    upload=$(cut -d " " -f 10 <<< $net_dev)
}

get_cpu() {
    cpu_idle=()
    cpu_total=$(bc <<< "$(cut -d " " -f 1 /proc/uptime) * 100" | cut -d "." -f 1)
    cpu_stat=$(cat /proc/stat | grep -E "cpu[0-9]" | xargs)
    for i in $(seq 0 $(($core_num - 1))); do 
        cpu_idle+=($(echo $cpu_stat | cut -d " " -f $((11 * $i + 5))))
    done
}

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

get_uptime () {
    uptime_seconds=$(cut -d " " -f 1 /proc/uptime | cut -d "." -f 1)
    uptime_days=$(bc <<< "$uptime_seconds / 86400")
    uptime_seconds=$(bc <<< "$uptime_seconds - $uptime_days * 86400")
    uptime_hours=$(bc <<< "$uptime_seconds / 3600")
    uptime_seconds=$(bc <<< "$uptime_seconds - $uptime_hours * 3600")
    uptime_minutes=$(bc <<< "$uptime_seconds / 60")
    uptime_seconds=$(bc <<< "$uptime_seconds - $uptime_minutes * 60")
}

get_battery () {
    battery_now=$(cat /sys/class/power_supply/BAT0/uevent | grep ENERGY_NOW= | cut -d "=" -f 2)
    battery_percentage=$(bc <<< "scale=2; 100*$battery_now/$battery_full")
}

get_load () {
    load=$(cut -d " " -f 1-3 /proc/loadavg)
}

get_memory () {
    mem_info=$(head -n 3 /proc/meminfo | tail -n 2)
    mem_free=$(head -n 1 <<< $mem_info | xargs | cut -d " " -f 2 | numfmt --from-unit=ki --to=iec --format=%.2f)
    mem_available=$(tail -n 1 <<< $mem_info | xargs | cut -d " " -f 2 | numfmt --from-unit=ki --to=iec --format=%.2f)
}

update () {
    get_net
    calculate_cpu
    get_uptime
    get_battery
    get_load
    get_memory

    echo "System status"
    echo -n "Download: " && (echo $(($download - $downzero)) | numfmt --to=iec)
    echo -n "Upload: " && (echo $(($upload - $upzero)) | numfmt --to=iec)
    for i in $(seq 0 $(($core_num - 1))); do
        echo "cpu$i: ${cpu_usage[$i]}% | $(cat /sys/devices/system/cpu/cpu$i/cpufreq/scaling_cur_freq)"
    done
    echo "Uptime: ${uptime_days}d ${uptime_hours}h ${uptime_minutes}m ${uptime_seconds}s"
    echo "Battery: ${battery_percentage}%"
    echo "Average load (over last 1/5/15minuts): $load"
    echo "Available memory: ${mem_available}B/${memory_total}B (${mem_free}B free)"
}

init

while :
do
    sleep 1
    clear
    update
done
